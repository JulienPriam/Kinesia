/*!
* \file UTest_session_list.c
* \brief Functions to test session list related functions
*/

#include "../src/model/structures.h"
#include "../src/controller/display_helpers.h"
#include "../src/model/patient_manager.h"
#include "UTest_session_list.h"
#include "../src/model/session_manager.h"

#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*!
 * \brief Allocate an empty sessionList for tests
 *
 * \param[in] state Pointer to communicate data
 * \param[out] -1 if error occured, 0 otherwise
*/
static int setup_sessionList_empty(void **state){
    SessionList *l = malloc(sizeof(SessionList));
    if(l == NULL) return -1;
    initList(l);
    assert_non_null(l);
    assert_null(l->current);
    assert_null(l->first);
    assert_null(l->last);
    *state = l;
    return 0;
}

/*!
 * \brief Allocate an nonempty sessionList for tests
 *
 * \param[in] state Pointer to communicate data
 * \param[out] -1 if error occured, 0 otherwise
*/
static int setup_sessionList_non_empty(void **state){
    SessionList *l = malloc(sizeof(SessionList));
    if(l == NULL) return -1;
    initList(l);
    assert_non_null(l);
    assert_null(l->current);
    assert_null(l->first);
    assert_null(l->last);

    insertFirst(l, "nom", "obs", 12, 3, 0, 0, 0, 0, "0", 0, 0, 1);
    insertFirst(l, "nom2", "obs2", 15, 14, 13, 12, 11, 10, "0", 0, 2, 3);
    *state = l;
    return 0;
}

/*!
 * \brief test isEmpty and insertFirst functions
 *
 * Check if the functions can detect empty lists,
 * and if is able to insert data in first position
 *
 * \param[in] state Pointer to communicate data
*/
static void test_isEmpty_insertFirst(void **state) {
    SessionList *l = *state;
    assert_int_equal(-1, isEmpty(l));

    assert_int_equal(0, insertFirst(l, "nom", "obs", 12, 3, 0, 0, 0, 0, "0", 0, 0, 1));

    assert_non_null(l->first);

    assert_null(l->first->previous);
    assert_string_equal("nom", l->first->session.sessionName);
    assert_string_equal("obs", l->first->session.observations);

    assert_int_equal(0, l->last->session.nextSessionDate.day);
    assert_int_equal(0, l->last->session.nextSessionDate.month);
    assert_int_equal(0, l->last->session.nextSessionDate.year);

    assert_int_equal(12, l->first->session.sessionDate.day);
    assert_int_equal(3, l->first->session.sessionDate.month);
    assert_int_equal(0, l->first->session.sessionDate.year);

    assert_int_equal(0, l->first->session.idSession);
    assert_int_equal(1, l->first->session.idFolder);

    assert_int_equal(0, isEmpty(l));
}

/*!
 * \brief test setOnFirst function
 * Test if the function can rewind the list progression
 *
 * \param[in] state Pointer to communicate data
*/
static void test_setOnFirst(void **state) {
    SessionList *l = *state;
    l->current = NULL;
    setOnFirst(l);
    assert_string_equal("nom2", l->current->session.sessionName);
}

/*!
 * \brief test setOnLast function
 * Test if the function can go to the end of the list
 *
 * \param[in] state Pointer to communicate data
*/
static void test_setOnLast(void **state) {
    SessionList *l = *state;
    l->current = NULL;
    setOnLast(l);
    assert_string_equal("nom", l->current->session.sessionName);
}

/*!
 * \brief test insertLast function
 * Check if a session can be added at the end of the list
 *
 * \param[in] state Pointer to communicate data
*/
static void test_insertLast(void **state) {
    SessionList *l = *state;
    insertLast(l, "nom3", "obs3", 12, 3, 0, 0, 0, 0, "8", 0, 0, 1);

    assert_non_null(l->last);

    assert_null(l->last->next);
    assert_string_equal("nom3", l->last->session.sessionName);
    assert_string_equal("obs3", l->last->session.observations);

    assert_int_equal(0, l->last->session.nextSessionDate.day);
    assert_int_equal(0, l->last->session.nextSessionDate.month);
    assert_int_equal(0, l->last->session.nextSessionDate.year);

    assert_int_equal(12, l->last->session.sessionDate.day);
    assert_int_equal(3, l->last->session.sessionDate.month);
    assert_int_equal(0, l->last->session.sessionDate.year);

    assert_int_equal(0, l->last->session.idSession);
    assert_int_equal(1, l->last->session.idFolder);

    assert_int_equal(0, isEmpty(l));
}

/*!
 * \brief test insertLast and isEmpty functions
 *
 * \param[in] state Pointer to communicate data
*/
static void test_insertLast_emptyList(void **state) {
    SessionList *l = *state;
    insertLast(l, "nom3", "obs3", 12, 3, 0, 0, 0, 0, "0", 0, 0, 1);

    assert_non_null(l->last);

    assert_null(l->last->next);
    assert_string_equal("nom3", l->first->session.sessionName);
    assert_string_equal("obs3", l->last->session.observations);

    assert_int_equal(0, l->last->session.nextSessionDate.day);
    assert_int_equal(0, l->last->session.nextSessionDate.month);
    assert_int_equal(0, l->last->session.nextSessionDate.year);

    assert_int_equal(12, l->last->session.sessionDate.day);
    assert_int_equal(3, l->last->session.sessionDate.month);
    assert_int_equal(0, l->last->session.sessionDate.year);

    assert_int_equal(0, l->last->session.idSession);
    assert_int_equal(1, l->last->session.idFolder);

    assert_int_equal(0, isEmpty(l));
}

/*!
 * \brief test isOutOfList functions
 * Check if the function can detect that the cursor is out of list
 *
 * \param[in] state Pointer to communicate data
*/
static void test_setOnNext_isOutOfList(void **state) {
    SessionList *l = *state;
    setOnFirst(l);
    assert_string_equal("nom2", l->current->session.sessionName);
    setOnNext(l);
    assert_string_equal("nom", l->current->session.sessionName);
    assert_int_equal(0, isOutOfList(l));
    setOnNext(l);
    assert_int_equal(-1, isOutOfList(l));
}

/*!
 * \brief test deleteFirst function
 * Check if the first session of a list can be deleted
 *
 * \param[in] state Pointer to communicate data
*/
static void test_deleteFirst(void **state) {
    SessionList *l = *state;
    deleteFirst(l);
    assert_string_equal("nom", l->first->session.sessionName);
    assert_string_equal("nom", l->last->session.sessionName);
    setOnFirst(l);
    setOnNext(l);
    assert_int_equal(-1, isOutOfList(l));
    assert_null(l->last->next);
}

/*!
 * \brief test deleteCurrent function
 * Check if the current session of a list can be deleted
 *
 * \param[in] state Pointer to communicate data
*/
static void test_deleteCurrent(void **state) {
    SessionList *l = *state;
    insertLast(l, "nom3", "obs3", 12, 3, 0, 0, 0, 0, "0", 0, 0, 1);
    setOnFirst(l);
    setOnNext(l);
    deleteCurrent(l);
    setOnFirst(l);
    assert_string_equal("nom2", l->current->session.sessionName);
    setOnNext(l);
    assert_string_equal("nom3", l->current->session.sessionName);
    setOnLast(l);
    assert_string_equal("nom3", l->current->session.sessionName);
}

/*!
 * \brief test pointNthElement function
 * Check if a random element can be selected
 *
 * \param[in] state Pointer to communicate data
*/
static void test_pointNthElement(void **state) {
    SessionList *l = *state;
    assert_int_equal(0, pointNthElement(l, 2));
    assert_string_equal("nom", l->current->session.sessionName);
    assert_int_equal(-1, pointNthElement(l, 3));
}

/*!
 * \brief test pointNthElement function
 * Check if a random element can be deleted
 *
 * \param[in] state Pointer to communicate data
*/
static void test_deleteNthElement(void **state) {
    SessionList *l = *state;
    insertLast(l, "nom3", "obs3", 12, 3, 0, 0, 0, 0,"0", 0, 0, 1);
    assert_int_equal(0, deleteNthElement(l, 2));
    assert_string_equal("nom3", l->last->session.sessionName);
    assert_string_equal("nom2", l->first->session.sessionName);
}

/*!
 * \brief deallocate function
 * Deallocate all needed information during tests
*/
static int teardown(void **state) {
    SessionList *l = *state;
    freeList(l);
    free(l);
    return 0;
}

/*!
 * \brief Run tests related to session list
*/
int main_session_list(void)
{

    const struct CMUnitTest tests_session_list[]=
            {
                    cmocka_unit_test_setup_teardown(test_isEmpty_insertFirst, setup_sessionList_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_setOnFirst, setup_sessionList_non_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_setOnLast, setup_sessionList_non_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_insertLast, setup_sessionList_non_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_insertLast_emptyList, setup_sessionList_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_setOnNext_isOutOfList, setup_sessionList_non_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_deleteFirst, setup_sessionList_non_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_deleteCurrent, setup_sessionList_non_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_pointNthElement, setup_sessionList_non_empty, teardown),
                    cmocka_unit_test_setup_teardown(test_deleteNthElement, setup_sessionList_non_empty, teardown)
            };
    return cmocka_run_group_tests_name("Test session list module",tests_session_list,NULL,NULL);
}
