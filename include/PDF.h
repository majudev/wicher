#ifndef PDF_GEN_H
#define PDF_GEN_H
#include "hpdf.h"
//#include "grid_sheet.h"
#include <vector>
#include <string>

#define TITLE_SIZE 32
#define SUBTITLE_SIZE 16
#define LOGO_SIZE 150
#define TEXT_SIZE 12

#define UD_MARGIN 55
#define LR_MARGIN 45

#define CELL_HEIGHT 15
#define CELL_HEADER_TEXT_SIZE 10
#define CELL_TEXT_SIZE 10

namespace Wicher {
namespace PDF{
	class Entry{
		public:
			Entry();
			Entry(std::string name, std::string type, std::vector<int> ids, std::string comment);
			std::string name;
			std::string type;
			std::vector<int> ids;
			std::string comment;
	};
	class EntryGen{
		public:
			EntryGen();
			void append(int id, std::string name, std::string type);
			std::vector<Entry> & get_entries();
		protected:
			std::vector<Entry> entries;
	};
	bool generate_wz(std::string outname, std::string id, std::string issuant, std::string receiver, std::string date, std::string purpose, std::string return_date, bool comment, std::vector<Entry> entries);
	bool generate_pz(std::string outname, std::string id, std::string wz_id, std::string issuant, std::string receiver, std::string date, bool comment, std::vector<Entry> entries);
	bool generate_pz2(std::string outname, std::string id, std::string wz_id, std::string issuant, std::string receiver, std::string date, bool comment, std::vector<Entry> entries);
}
}

#endif
