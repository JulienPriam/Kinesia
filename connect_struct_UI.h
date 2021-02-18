//
// Created by julien on 09/02/2021.
//

#ifndef LOGICIEL_KINE_CONNECT_STRUCT_UI_H
#define LOGICIEL_KINE_CONNECT_STRUCT_UI_H

#include "structures.h"
#include <string.h>

char *get_name_UI(Patient *patient);
char *get_date_UI(Date *date);
char *get_height_UI(Patient *patient);
char *get_weight_UI(Patient *patient);
char *get_height_weight_UI(Patient *patient);
char *get_first_consultation_UI(Patient *patient);
char *get_adress_UI(Patient *patient);
char *get_formatted_folder_title_UI(Folder *folder);
char *get_formatted_folder_infos_UI(Folder *folder);
char *get_indicator_files_UI(Folder *folder);

void free_info_UI(char *info);

#endif //LOGICIEL_KINE_CONNECT_STRUCT_UI_H
