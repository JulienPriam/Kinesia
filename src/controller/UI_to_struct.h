/*!
* \file UI_to_struct.h
* \brief File with functions used to parse data from UI entries to structures
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../model/structures.h"


#ifndef LOGICIEL_KINE_CONNECT_UI_STRUCT_H
#define LOGICIEL_KINE_CONNECT_UI_STRUCT_H

typedef struct{
    Session *session;
    GtkWidget *sessionName;
    GtkWidget *sessionDate;
    GtkWidget *nextSessionDate;
    GtkWidget *observations;
    int origin;                     //0 for new session; 1 to edit session
}NewSessionEntries;

Date *parseDate(char *stringDate);
void saveNewSession(NewSessionEntries *new_session);

#endif //LOGICIEL_KINE_CONNECT_UI_STRUCT_H
