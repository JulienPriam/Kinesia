#include "structures.h"
#include "connect_struct_UI.h"
#include "patient.h"

//#include "../src/structures.h"
//#include "../src/connect_struct_UI.h"
//#include "../src/patient.h"

#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*Add tests here*/
static int setup_patient(void **state){
    Patient *patient = getPatient(1);
    if(patient == NULL) return -1;

	assert_non_null(patient);
	*state = patient;
	return 0;
}

static void test_get_name_UI(void **state){
    Patient * patient = (Patient *) (*state);
    assert_string_equal("Francois bla Claude", get_name_UI(patient));
}

static int teardown(void **state){
    Patient * patient = (Patient *) (*state);
    freePatient(&patient);
    return 0;
}


int main(void)
{

    const struct CMUnitTest tests_counter[]=
    {
            cmocka_unit_test_setup_teardown(test_get_name_UI, setup_patient, teardown),
    };
    return cmocka_run_group_tests_name("Test counter module",tests_counter,NULL,NULL);
}
