#include "course.h"

#include <stdlib.h>

struct course* course_create(enum subject subj, uint16_t code)
{
    struct course* c = malloc(sizeof(struct course));
    c->subj = subj;
    c->code = code;
    c->refcount = 1;
    c->passing_score_grad = 65;
    c->passing_score_undergrad = 50;
    c->full_score = 100;
    return c;
}

/** Retrieve a course's subject. */
enum subject course_subject(const struct course* c)
{
    return c->subj;
}

/** Retrieve a course's course code. */
uint16_t course_code(const struct course* c)
{
    return c->code;
}

/** Increment a course's refcount. */
void course_hold(struct course* c)
{
    c->refcount++;
}

/** Decrement a course's refcount (optionally freeing it). */
void course_release(struct course* c)
{
    if (--c->refcount == 0) {
        free(c);
    }
}

/** Retrieve the current reference count of a course. */
int course_refcount(const struct course* c)
{
    return c->refcount;
}
