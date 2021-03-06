/*!
* \file editor_views.h
* \brief File with callback functions to launch dialog boxes across the software
*/

#ifndef SESSION_CONTROLLER_H
#define SESSION_CONTROLLER_H

#include "../model/structures.h"
#include "../model/patient_manager.h"
#include "../model/BDD_to_struct_patient.h"
#include "../controller/extern_files_manager.h"

/**
 * \brief Structure to pass a patient and a window in a callback function
 *
 * This structure is used to pass many arguments in a callback function which has only
 * one argument.
*/
typedef struct {
    Patient *patient;       /**< Patient to be edited */
    GtkWidget *window;      /**< Parent window to be reload after changes */
    int origin;             /**< 0 if new patient, 1 if edition of existing Patient */
}Patient_window;

/**
 * \brief Structure to choose the warning
 *
 * This structure enables the callback to act on the patient, choose the action to be done
 * and reload the parent window after changes.
*/
typedef struct {
    int patientID;         /**< ID of the Patient to be deleted or archived */
    int actionType;        /**< Type of warning: 0 = "delete" or 1 = "archive" */
    GtkWidget *window;     /**< Parent window to be reload after changes */
}WarningType;

/**
 * \brief Structure to choose the folder editor
*/
typedef struct{
    Folder *folder;         /**< Folder to be edited */
    int edit_new;           /**< Is the folder new (1) or alredy existing (0) */
    GtkWidget *window;      /**< Parent window to be refreshed */
}FolderEditorStruct;

/**
 * \brief Structure to communicate the Patient identifier in callback
*/
typedef struct{
    int idPatient;          /**< Patient identifier */
    GtkWidget *window;      /**< Parent window to be refreshed */
}IdPatientCallback;

/**
 * \brief Structure to choose the type of media to open
 *
 * This structure enables the callback to know what type of media to process
 * and which Patient it is to store it in the right place
*/
typedef struct {
    int patientID;                /**< Patient concerned */
    int folderID;                 /**< Identifier of the concerned Folder */
    int mediaType;                /**< Type of media to be stored in the software: 0 = "profile" 1 = other */
    int isNewPatient;             /**< Boolean to know if the patient is new: 0 = existing, 1 = new */
    GtkWidget *counterLabel;      /**< Label containing the number of files */
}MediaType;

/**
 * \brief Structure to communicate the settings of the window
 *
 * Enables to communicate css parameters
*/
typedef struct {
    GtkWidget *window;            /**< Parent window */
    int cssMode;                  /**< UI theme: 0 = light or 1 = dark */
}SoftwareSettings;

void launchFolderEditor(GtkWidget *button, FolderEditorStruct *foldEditStruct);
void launchNewFolderEditor(GtkWidget *button, IdPatientCallback *idPatientCall);
void launchPatientEditor(GtkWidget *but_edit, Patient_window *patient_window);
void launchNewPatientEditor(GtkWidget *but_new, GtkWidget *window);
void launchFileChooser(GtkWidget *photo_button, MediaType *mediaChooser);
void changeDateCallback(GtkWidget *calendar, GtkWidget *entry);
void launchCalendar(GtkWidget *button, GtkWidget *entry);
void launchPatientWarning(GtkWidget *button, WarningType *warning);
void launchSettingsEditor(GtkWidget *button, SoftwareSettings *settings);
void launchAttachmentListViewer(GtkWidget *button, MediaType *attachmentProperties);
void launchDeleteElement(GtkWidget *button, DeleteElements *element);

#endif
