#include <stdio.h>

#include "course.h"
#include "student.h"

int main()
{
    struct student_id alice_id = { .sid_year = 2021, .sid_serial = 123456 };
    struct student* alice = student_create(alice_id, false);

    struct student_id bob_id = { .sid_year = 2018, .sid_serial = 234567 };
    struct student* bob = student_create(bob_id, true);

    struct student_id charlie_id = { .sid_year = 2019, .sid_serial = 345678 };
    struct student* charlie = student_create(charlie_id, true);

    printf("--------------------------------\n");

    printf("Alice: %d-%d, %s.\n",
        alice->id.sid_year, alice->id.sid_serial,
        alice->graduate ? "graduate" : "undergraduate");

    printf("Bob: %d-%d, %s.\n",
        bob->id.sid_year, bob->id.sid_serial,
        bob->graduate ? "graduate" : "undergraduate");

    printf("Charlie: %d-%d, %s.\n",
        charlie->id.sid_year, charlie->id.sid_serial,
        charlie->graduate ? "graduate" : "undergraduate");

    printf("--------------------------------\n");

    struct course* e6001 = course_create(SUBJ_ECE, 6001);
    struct course* e6002 = course_create(SUBJ_ECE, 6002);
    struct course* e6003 = course_create(SUBJ_ECE, 6003);
    struct course* e6004 = course_create(SUBJ_ECE, 6004);

    struct course* c9006 = course_create(SUBJ_ENGI, 9006);
    struct course* c9007 = course_create(SUBJ_ENGI, 9007);
    struct course* c9008 = course_create(SUBJ_ENGI, 9008);
    struct course* c9009 = course_create(SUBJ_ENGI, 9009);

    printf("#\tPass-mark(Grad/Undergrad)\tFull-mark\n");
    printf("ECE 6001\t%.0lf/%.0lf\t%.0lf\n", e6001->passing_score_grad, e6001->passing_score_undergrad, e6001->full_score);
    printf("ECE 6002\t%.0lf/%.0lf\t%.0lf\n", e6002->passing_score_grad, e6002->passing_score_undergrad, e6002->full_score);
    printf("ECE 6003\t%.0lf/%.0lf\t%.0lf\n", e6003->passing_score_grad, e6003->passing_score_undergrad, e6003->full_score);
    printf("ECE 6004\t%.0lf/%.0lf\t%.0lf\n", e6004->passing_score_grad, e6004->passing_score_undergrad, e6004->full_score);
    printf("ENGI 9006\t%.0lf/%.0lf\t%.0lf\n", c9006->passing_score_grad, c9006->passing_score_undergrad, c9006->full_score);
    printf("ENGI 9007\t%.0lf/%.0lf\t%.0lf\n", c9007->passing_score_grad, c9007->passing_score_undergrad, c9007->full_score);
    printf("ENGI 9008\t%.0lf/%.0lf\t%.0lf\n", c9008->passing_score_grad, c9008->passing_score_undergrad, c9008->full_score);
    printf("ENGI 9009\t%.0lf/%.0lf\t%.0lf\n", c9009->passing_score_grad, c9009->passing_score_undergrad, c9009->full_score);

    printf("--------------------------------\n");

    student_take(alice, e6001, 96);
    student_take(alice, e6002, 97);
    student_take(alice, e6003, 98);
    student_take(alice, e6004, 99);

    printf("Alice registered e6001, e6002, e6003 and e6004.\n");
    printf("Alice's mark in ECE 6001 is %d\n", student_grade(alice, e6001));
    printf("Alice's mark in ECE 6002 is %d\n", student_grade(alice, e6002));
    printf("Alice's mark in ECE 6003 is %d\n", student_grade(alice, e6003));
    printf("Alice's mark in ECE 6004 is %d\n", student_grade(alice, e6004));
    printf("Alice's passed average mark is %.1lf\n", student_passed_average(alice));
    printf("She is %s.\n", student_promotable(alice) ? "promotable" : "not promotable");

    printf("--------------------------------\n");

    student_take(bob, c9006, 67);
    student_take(bob, c9007, 68);
    student_take(bob, c9008, 69);
    student_take(bob, c9009, 70);

    printf("Bob registered c9006, c9007, c9008 and c9009.\n");
    printf("Bob's mark in ENGI 9006 is %d\n", student_grade(bob, c9006));
    printf("Bob's mark in ENGI 9007 is %d\n", student_grade(bob, c9007));
    printf("Bob's mark in ENGI 9008 is %d\n", student_grade(bob, c9008));
    printf("Bob's mark in ENGI 9009 is %d\n", student_grade(bob, c9009));
    printf("Bob's passed average mark is %.1lf\n", student_passed_average(bob));
    printf("He is %s.\n", student_promotable(bob) ? "promotable" : "not promotable");

    printf("--------------------------------\n");

    student_take(charlie, e6001, 45);
    student_take(charlie, e6002, 99);
    student_take(charlie, c9007, 46);
    student_take(charlie, c9008, 98);

    printf("Charlie registered e6001, e6002, c9007 and c9008.\n");
    printf("Charlie's mark in ECE 6001 is %d\n", student_grade(charlie, e6001));
    printf("Charlie's mark in ECE 6002 is %d\n", student_grade(charlie, e6002));
    printf("Charlie's mark in ENGI 9007 is %d\n", student_grade(charlie, c9007));
    printf("Charlie's mark in ENGI 9008 is %d\n", student_grade(charlie, c9008));
    printf("Charlie's passed average mark is %.1lf\n", student_passed_average(charlie));
    printf("He is %s.\n", student_promotable(charlie) ? "promotable" : "not promotable");

    printf("--------------------------------\n");

    course_release(e6001);
    course_release(e6002);
    course_release(e6003);
    course_release(e6004);

    course_release(c9006);
    course_release(c9007);
    course_release(c9008);
    course_release(c9009);

    student_free(alice);
    student_free(bob);

    printf("Finished successfully\n");

    return 0;
}
