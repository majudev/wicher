#include "ListsManager.h"

Wicher::ColumnModels::TypeColumns::TypeColumns(){ add(id); add(name); add(available); add(unavailable); add(total); add(comment); }
Wicher::ColumnModels::EntryColumns::EntryColumns(){ add(id); add(available); add(wz_id); add(comment); add(checkbox); add(type); }
Wicher::ColumnModels::WZColumns::WZColumns(){ add(id); add(date); add(person); add(return_date); add(comment); }
Wicher::ColumnModels::PZColumns::PZColumns(){ add(id); add(wz_id); add(date); add(person); add(comment); }
Wicher::ColumnModels::HistoryColumns::HistoryColumns(){ add(id); add(data); }
