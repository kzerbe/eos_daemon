#ifndef MACTABLEMANAGER_H
#define MACTABLEMANAGER_H

#include <memory>

#include <eos/mac_table.h>

class MacTableManager
{
    public:
        MacTableManager();
        virtual ~MacTableManager();

    private:
        eos::mac_table_mgr* m_macTableManager;
};

#endif // MACTABLEMANAGER_H
