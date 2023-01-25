#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "course.h"
#include "student.h"

#define INITIAL_CAPACITY (16)
#define ARRAY_NEW(type, n) (type*)malloc((n) * sizeof(type))

static struct grade** grades_array_new(int capacity)
{
    return ARRAY_NEW(struct grade*, capacity);
}

static struct grade* grade_new(struct course* c, u_int8_t g)
{
    struct grade* grade = ARRAY_NEW(struct grade, 1);
    grade->course = c;
    grade->grade = g;
    return grade;
}

static void student_ensure_capacity(struct student* s, int capacity)
{
    if (s->capacity >= capacity) {
        return;
    }
    s->capacity *= 2;
    s->grades = realloc(s->grades, s->capacity * sizeof(struct grade*));
}

static void grades_array_add(struct student* s, struct grade* g)
{
    student_ensure_capacity(s, s->num_courses + 1);
    s->grades[s->num_courses++] = g;
}

struct student* student_create(struct student_id id, bool grad_student)
{
    struct student* s = malloc(sizeof(struct student));
    s->id = id;
    s->capacity = INITIAL_CAPACITY;
    s->grades = grades_array_new(s->capacity);
    s->num_courses = 0;
    s->graduate = grad_student;
    return s;
}

void student_free(struct student* s)
{
    for (int i = 0; i < s->num_courses; i++) {
        course_release(s->grades[i]->course);
        free(s->grades[i]);
    }
    free(s->grades);
    free(s);
}

/**
 * Check if a student has taken a course.
 * @returns the pointer to grade if the student has taken the course, NULL otherwise
 */
struct grade* student_find_grade(
    struct student* s,
    int course_code)
{
    for (int i = 0; i < s->num_courses; ++i) {
        if (s->grades[i]->course->code == course_code) {
            return s->grades[i];
        }
    }
    return NULL;
}

void student_take(struct student* s, struct course* c, uint8_t grade)
{
    if (student_find_grade(s, c->code)) {
        return;
    }
    grades_array_add(s, grade_new(c, grade));
    course_hold(c);
}

int student_grade(struct student* s, struct course* c)
{
    struct grade* g = student_find_grade(s, c->code);
    return g ? g->grade : -1;
}

/**
 * Compute the average of all grades that a student has passed.
 * @param s the student
 * @param out_num_passed nullable, out, the number of courses that the student has passed
 * @param out_num_failed nullable, out, the number of courses that the student has failed
 * @param out_average_passed_ratio nullable, out, the average ratio (0~1) of all passed courses
 * @param out_average_all_ratio nullable, out, the average ratio (0~1) of all courses
 */
static void student_average_of_passed(
    const struct student* s,
    int* out_num_passed,
    int* out_num_failed,
    double* out_average_passed_ratio,
    double* out_average_all_ratio)
{
    double sum_score_passed = 0;
    double sum_score_all = 0;
    double sum_score_full_passed = 0;
    double sum_score_full_all = 0;
    int count = 0;

#define TEST_AND_SET(out, val) \
    ((out) && (*(out) = (val)))

    TEST_AND_SET(out_num_passed, 0);
    TEST_AND_SET(out_num_failed, 0);

    for (int i = 0; i < s->num_courses; ++i) {
        struct grade* g = s->grades[i];
        struct course* c = g->course;
        sum_score_full_all += c->full_score;
        sum_score_all += g->grade;

        if (
            g->grade >= (s->graduate
                    ? c->passing_score_grad
                    : c->passing_score_undergrad)) {
            sum_score_passed += s->grades[i]->grade;
            sum_score_full_passed += c->full_score;
            TEST_AND_SET(out_num_passed, *out_num_passed + 1);
            count++;
        } else {
            TEST_AND_SET(out_num_failed, *out_num_failed + 1);
        }
    }

    TEST_AND_SET(out_average_passed_ratio, sum_score_passed / sum_score_full_passed);
    TEST_AND_SET(out_average_all_ratio, sum_score_all / sum_score_full_all);
#undef TEST_AND_SET
}

double student_passed_average(const struct student* s)
{
    double average_ratio = 0;
    student_average_of_passed(s, NULL, NULL, &average_ratio, NULL);
    return average_ratio * 100;
}

bool student_promotable(const struct student* s)
{
    int num_failed = 0;
    double average_all_ratio = 0;
    student_average_of_passed(s, NULL, &num_failed, NULL, &average_all_ratio);

    if (s->graduate) {
        return num_failed <= 1;
    }
    return average_all_ratio >= 0.6;
}
