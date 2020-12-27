#ifndef PAGE_OPTION_H
#define PAGE_OPTION_H

typedef int PageOptionID;
#define PAGE_OPTION_ID_CONFIRM  2002

#define calculatePageOptionIdFromPageIdAndSelectedNum(PAGE_ID, SELECTED_NUM) (PAGE_ID*10+SELECTED_NUM)

#endif // PAGE_OPTION_H