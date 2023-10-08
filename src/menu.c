#include <swilib.h>
#include <stdlib.h>
#include <sie/sie.h>

SIE_MENU_LIST *InitMenu(const char **names, void (**procs)(void), unsigned int count) {
    SIE_MENU_LIST_ITEM *items = malloc(sizeof(SIE_MENU_LIST_ITEM) * count);
    for (unsigned int i = 0; i < count; i++) {
        SIE_MENU_LIST_ITEM *item = &(items[i]);
        zeromem(item, sizeof(SIE_MENU_LIST_ITEM));

        size_t len = strlen(names[i]);
        item->ws = AllocWS((int)(len + 1));
        wsprintf(item->ws, "%t", names[i]);
        item->proc = procs[i];
    }
    SIE_MENU_LIST *menu = NULL;
    menu = Sie_Menu_List_Init(items, count);
    return menu;
}

void DestroyMenu(SIE_MENU_LIST *menu) {
    Sie_Menu_List_Destroy(menu);
}

void AddMenuItem(char ***names, void (***procs)(), unsigned int *count, const char *name, void (*proc)()) {
    unsigned int c = (*count) + 1;
    *names = realloc(*names, sizeof(char *) * c);
    *procs = realloc(*procs, sizeof(void *) * c);
    (*names)[c - 1] = malloc(64);
    strcpy((*names)[c - 1], name);
    (*procs)[c - 1] = proc;
    *count = c;
}

void DestroyMenuItems(char **names, void (**procs)(), unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        mfree(names[i]);
    }
    mfree(names);
    mfree(procs);
}