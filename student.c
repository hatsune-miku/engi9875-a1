#include "student.h"

struct student *student_create(struct student_id, bool grad_student)
{
    struct student *s = malloc(sizeof(struct student));
    s->id = id;
    s->grad_student = grad_student;
    s->courses = NULL;
    s->num_courses = 0;
    return s;
}

void student_free(struct student *);

void student_take(struct student *s, struct course *, uint8_t grade);

int student_grade(struct student *, struct course *);

double student_passed_average(const struct student *);

bool student_promotable(const struct student *);
