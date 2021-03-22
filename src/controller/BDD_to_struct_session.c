//
// Created by salome on 22/03/2021.
//

#include "BDD_to_struct_session.h"
#include "../model/session_manager.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

//Recupération d'une séance
Session * getSession(int idSession){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    Session *session;

    session = (Session*)malloc(sizeof(Session));

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "SELECT * FROM seance WHERE idSeance=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idSession);

    sqlite3_step(stmt);

    initSession(session,(char*)sqlite3_column_text(stmt,9),(char*)sqlite3_column_text(stmt,8),
                sqlite3_column_int(stmt,4),sqlite3_column_int(stmt,3),sqlite3_column_int(stmt,2),
                sqlite3_column_int(stmt,7),sqlite3_column_int(stmt,6),sqlite3_column_int(stmt,5),
                sqlite3_column_int(stmt,0),sqlite3_column_int(stmt,1));

    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return session;

}

//Array of session id from a folder id
int * getSessionId(int idFolder){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    sqlite3_stmt *stmt=NULL;
    int *tab_id;

    if((tab_id = (int*)malloc(sizeof(int)*NB_MAX_SESSION)) == NULL ){
        return NULL;
    }

    //Ouverture de la bdd
    rc = sqlite3_open(DB_PATH, &db);

    //Test de l'ouverture
    if( rc ) {
        fprintf(stderr, "Can't open model: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr,"Opened database successfully\n");
    }

    //Creation de la requête
    sql = "SELECT idSeance FROM seance WHERE idDossier=?";

    rc = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Prepare SELECT error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_bind_int(stmt,1,idFolder);

    int i;
    i=0;
    while(sqlite3_step(stmt) == SQLITE_ROW){
        tab_id[i] = sqlite3_column_int(stmt,0);
        i++;
    }
    sqlite3_finalize(stmt);

    //Fermeture de la bdd
    sqlite3_close(db);
    return tab_id;

}