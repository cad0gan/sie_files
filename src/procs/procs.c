#include <swilib.h>
#include <stdlib.h>
#include <sie/sie.h>
#include "../ipc.h"

extern SIE_FILE *CURRENT_FILE;
extern SIE_FILE *COPY_FILES, *MOVE_FILES;
extern unsigned int MAIN_GUI_ID;
extern SIE_GUI_STACK *GUI_STACK;

void CreateDiskInfoGUI() {
    ShowMSG(1, (int)"Create disk info gui");
}

void CreateFile() {
    ShowMSG(1, (int)"Create file");
}

void CreateDir() {
    ShowMSG(1, (int)"Create directory");
}

void CopyFile() {
    if (COPY_FILES) {
        Sie_FS_DestroyFiles(COPY_FILES);
    }
    COPY_FILES = Sie_FS_CopyFileElement(CURRENT_FILE);
    GUI_STACK = Sie_GUI_Stack_CloseChildren(GUI_STACK, MAIN_GUI_ID);
}

void MoveFile() {
    if (MOVE_FILES) {
        Sie_FS_DestroyFiles(MOVE_FILES);
    }
    MOVE_FILES = Sie_FS_CopyFileElement(CURRENT_FILE);
    GUI_STACK = Sie_GUI_Stack_CloseChildren(GUI_STACK, MAIN_GUI_ID);
}



/**********************************************************************************************************************/

void SetAsWallpaper() {
    const size_t len1 = strlen(CURRENT_FILE->dir_name);
    const size_t len2 = strlen(CURRENT_FILE->file_name);
    WSHDR *ws = AllocWS((int)(len1 + len2 + 1));
    wsprintf(ws, "%s%s", CURRENT_FILE->dir_name, CURRENT_FILE->file_name);
    Sie_Resources_SetWallpaper(ws);
    FreeWS(ws);
    GUI_STACK = Sie_GUI_Stack_CloseChildren(GUI_STACK, MAIN_GUI_ID);
}

/**********************************************************************************************************************/

void DeleteFiles(const SIE_FILE *files) {
    unsigned int err;
    SIE_FILE *p = (SIE_FILE*)files;
    while (p != NULL) {
        char *path = Sie_FS_GetPathByFile(p);
        if (p->file_attr & FA_DIRECTORY) {
            Sie_FS_RemoveDirRecursive(path);
        } else {
            _unlink(path, &err);
        }
        mfree(path);
        p = p->next;
    }
    GUI_STACK = Sie_GUI_Stack_CloseChildren(GUI_STACK, MAIN_GUI_ID);
    IPC_Redraw();
}