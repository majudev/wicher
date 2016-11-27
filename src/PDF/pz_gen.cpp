#include <iostream>
#include <iomanip>
#include <exception>
#include "PDF.h"
#include "Toolkit.h"

static void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data){
	std::cerr << "PDF: Haru error! Error: " << std::setbase(16) << error_no << std::setbase(10) << std::endl;
	if(detail_no) perror("Details");
	throw std::exception(); /* throw exception on error */
}

bool Wicher::PDF::generate_pz(std::string outname, std::string id, std::string wz_id, std::string issuant, std::string receiver, std::string date, bool comment, std::vector<Entry> entries){
	HPDF_Doc pdf = HPDF_New (error_handler, NULL); /* set error-handler */
	if (!pdf) {
		std::cerr << "PDF: Cannot create Haru instance." << std::endl;
		return false;
	}

	const char * page_title = "Przyjęcie zewnętrzne";
	const char * page_subtitle = "Szczep Żbicza Gromada";

	try {
		HPDF_Page page = HPDF_AddPage(pdf);
		HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
		HPDF_REAL width = HPDF_Page_GetWidth(page);
		HPDF_REAL height = HPDF_Page_GetHeight(page);
		HPDF_Page_SetLineWidth (page, 3);
		HPDF_Page_Rectangle (page, 0, 0, width, height);
		HPDF_Page_Stroke (page);

		const char * font = HPDF_LoadTTFontFromFile(pdf, "share/wicher/tt/arial.ttf", HPDF_TRUE);
		const char * font_bold = HPDF_LoadTTFontFromFile(pdf, "share/wicher/tt/arialbd.ttf", HPDF_TRUE);
		HPDF_UseUTFEncodings(pdf);
		HPDF_Font def_font = HPDF_GetFont(pdf, font, "UTF-8");
		HPDF_Font def_font_bold = HPDF_GetFont(pdf, font_bold, "UTF-8");
		
		/*title*/
		HPDF_Page_SetFontAndSize (page, def_font, TITLE_SIZE);
		HPDF_REAL tw = HPDF_Page_TextWidth (page, page_title);
		HPDF_Page_BeginText (page);
		HPDF_Page_TextOut (page, (width - tw - LOGO_SIZE) / 2 + LOGO_SIZE, height - UD_MARGIN - TITLE_SIZE, page_title);
		HPDF_Page_EndText (page);
		/*subtitle*/
		HPDF_Page_SetFontAndSize (page, def_font, SUBTITLE_SIZE);
		tw = HPDF_Page_TextWidth (page, page_subtitle);
		HPDF_Page_BeginText (page);
		HPDF_Page_TextOut (page, (width - tw - LOGO_SIZE) / 2 + LOGO_SIZE, height - UD_MARGIN - 2 - TITLE_SIZE - SUBTITLE_SIZE, page_subtitle);
		HPDF_Page_EndText (page);

		HPDF_INT step = (LOGO_SIZE - 2 - SUBTITLE_SIZE - 40)/6;

		HPDF_Page_BeginText (page);
		HPDF_Page_MoveTextPos (page, (width - LOGO_SIZE) / 2, height - UD_MARGIN - 2 - TITLE_SIZE - SUBTITLE_SIZE - 15 - TEXT_SIZE);

		HPDF_Page_SetFontAndSize (page, def_font, TEXT_SIZE);
		HPDF_Page_ShowText (page, "ID Przyjęcia: ");
		HPDF_Page_ShowText (page, id.c_str());
		HPDF_Page_MoveTextPos (page, 0, (-1)*step);
		HPDF_Page_ShowText (page, "ID Wydania: ");
		HPDF_Page_ShowText (page, wz_id.c_str());
		HPDF_Page_MoveTextPos (page, 0, (-1)*step);
		//HPDF_Page_ShowText (page, "Osoba przyjmująca: ");
		///HPDF_Page_ShowText (page, issuant.c_str());
		//HPDF_Page_MoveTextPos (page, 0, (-1)*step);
		HPDF_Page_ShowText (page, "Osoba: ");
		HPDF_Page_ShowText (page, receiver.c_str());
		HPDF_Page_MoveTextPos (page, 0, (-1)*step);
		HPDF_Page_ShowText (page, "Data wydania: ");
		HPDF_Page_ShowText (page, date.c_str());
		HPDF_Page_MoveTextPos (page, 0, (-1)*step);
		//HPDF_Page_ShowText (page, "Cel: ");
		//HPDF_Page_ShowText (page, purpose.c_str());
		//HPDF_Page_MoveTextPos (page, 0, (-1)*step);
		//HPDF_Page_ShowText (page, "Planowana data zwrotu: ");
		//HPDF_Page_ShowText (page, return_date.c_str());
		/*HPDF_Page_MoveTextPos (page, 0, (-1)*step);
		HPDF_Page_ShowText (page, "");*/

		HPDF_Page_EndText (page);

		HPDF_Image image;

		image = HPDF_LoadPngImageFromFile (pdf, "share/wicher/gui/ZG.png");

		/* Draw image to the canvas. */
		HPDF_Page_DrawImage (page, image, LR_MARGIN, height - UD_MARGIN - LOGO_SIZE, LOGO_SIZE, LOGO_SIZE);

		/* Drawing table */
		HPDF_Page_SetLineWidth (page, 1);
		float position = height - LOGO_SIZE - 2 - SUBTITLE_SIZE - 40 - (CELL_HEIGHT + 5);
		HPDF_Page_MoveTo (page, LR_MARGIN, position);
		HPDF_Page_LineTo (page, width - LR_MARGIN, position);
		HPDF_Page_MoveTo (page, LR_MARGIN, position - (CELL_HEIGHT + 5));
		HPDF_Page_LineTo (page, width - LR_MARGIN, position - (CELL_HEIGHT + 5));
		HPDF_Page_MoveTo (page, LR_MARGIN, position - (CELL_HEIGHT + 5));
		HPDF_Page_LineTo (page, LR_MARGIN, position);
		HPDF_Page_MoveTo (page, width - LR_MARGIN, position - (CELL_HEIGHT + 5));
		HPDF_Page_LineTo (page, width - LR_MARGIN, position);
		HPDF_Page_Stroke (page);
		
		const char * name_col_text = "Przedmiot";
		const char * id_col_text = "Oznaczenia";
		const char * count_col_text = "Ilość";
		const char * comment_col_text = "Komentarz";
		
		int COMMENT_WIDTH = 0;
		if(comment) COMMENT_WIDTH = 120;
		
		HPDF_Page_SetFontAndSize (page, def_font_bold, CELL_HEADER_TEXT_SIZE);
		
		tw = HPDF_Page_TextWidth (page, name_col_text);
		HPDF_Page_BeginText (page);
		HPDF_Page_MoveTextPos (page, LR_MARGIN + 5, position - ((CELL_HEIGHT + 5) + CELL_HEADER_TEXT_SIZE)/2 + 2);
		HPDF_Page_ShowText (page, name_col_text);
		HPDF_Page_EndText (page);
		
		tw = HPDF_Page_TextWidth (page, id_col_text);
		HPDF_Page_BeginText (page);
		HPDF_Page_MoveTextPos (page, LR_MARGIN + 285 - COMMENT_WIDTH/2, position - ((CELL_HEIGHT + 5) + CELL_HEADER_TEXT_SIZE)/2 + 2);
		HPDF_Page_ShowText (page, id_col_text);
		HPDF_Page_EndText (page);
		HPDF_Page_MoveTo (page, LR_MARGIN + 280 - COMMENT_WIDTH/2, position - (CELL_HEIGHT + 5));
		HPDF_Page_LineTo (page, LR_MARGIN + 280 - COMMENT_WIDTH/2, position);
		HPDF_Page_Stroke (page);
		
		tw = HPDF_Page_TextWidth (page, count_col_text);
		HPDF_Page_BeginText (page);
		HPDF_Page_MoveTextPos (page, LR_MARGIN + 455 - COMMENT_WIDTH, position - ((CELL_HEIGHT + 5) + CELL_HEADER_TEXT_SIZE)/2 + 2);
		HPDF_Page_ShowText (page, count_col_text);
		HPDF_Page_EndText (page);
		HPDF_Page_MoveTo (page, LR_MARGIN + 450 - COMMENT_WIDTH, position - (CELL_HEIGHT + 5));
		HPDF_Page_LineTo (page, LR_MARGIN + 450 - COMMENT_WIDTH, position);
		HPDF_Page_Stroke (page);
		
		if(comment){
			tw = HPDF_Page_TextWidth (page, comment_col_text);
			HPDF_Page_BeginText (page);
			HPDF_Page_MoveTextPos (page, width - LR_MARGIN - COMMENT_WIDTH + 5, position - ((CELL_HEIGHT + 5) + CELL_HEADER_TEXT_SIZE)/2 + 2);
			HPDF_Page_ShowText (page, comment_col_text);
			HPDF_Page_EndText (page);
			HPDF_Page_MoveTo (page, width - LR_MARGIN - COMMENT_WIDTH, position - (CELL_HEIGHT + 5));
			HPDF_Page_LineTo (page, width - LR_MARGIN - COMMENT_WIDTH, position);
			HPDF_Page_Stroke (page);
		}
		
		position -= CELL_HEIGHT + 5;
		HPDF_Page_SetFontAndSize (page, def_font, CELL_TEXT_SIZE);
		
		char buf[10];
		int page_n = 1;
		
		for(unsigned int i = 0; i != entries.size(); ++i){
			tw = HPDF_Page_TextWidth (page, entries[i].name.c_str());
			HPDF_Page_BeginText (page);
			HPDF_Page_MoveTextPos (page, LR_MARGIN + 5, position - (CELL_HEIGHT + CELL_TEXT_SIZE)/2 + 1);
			HPDF_Page_ShowText (page, entries[i].name.c_str());
			HPDF_Page_EndText (page);
			
			/*tw = HPDF_Page_TextWidth (page, buf);
			HPDF_Page_BeginText (page);
			HPDF_Page_MoveTextPos (page, width - LR_MARGIN - COMMENT_WIDTH - 5 - tw, position - (CELL_HEIGHT + CELL_TEXT_SIZE)/2 + 1);
			HPDF_Page_ShowText (page, buf);
			HPDF_Page_EndText (page);*/

			/*if(comment){
				tw = HPDF_Page_TextWidth (page, entries[i].comment.c_str());
				HPDF_Page_BeginText (page);
				HPDF_Page_MoveTextPos (page, width - LR_MARGIN - COMMENT_WIDTH + 5, position - (CELL_HEIGHT + CELL_TEXT_SIZE)/2 + 1);
				HPDF_Page_ShowText (page, entries[i].comment.c_str());
				HPDF_Page_EndText (page);
			}*/
			
			float comment_startpos = position;
			
			for(unsigned int j = 0; j != entries[i].ids.size(); ++j){
				HPDF_Page_SetLineWidth (page, 1);
				HPDF_Page_MoveTo (page, LR_MARGIN, position - CELL_HEIGHT);
				HPDF_Page_LineTo (page, LR_MARGIN, position);
				HPDF_Page_MoveTo (page, width - LR_MARGIN, position - CELL_HEIGHT);
				HPDF_Page_LineTo (page, width - LR_MARGIN, position);
				HPDF_Page_Stroke (page);
				
				HPDF_Page_SetLineWidth (page, 0.5);
				
				HPDF_Page_MoveTo (page, LR_MARGIN + 450 - COMMENT_WIDTH, position - CELL_HEIGHT);
				HPDF_Page_LineTo (page, LR_MARGIN + 450 - COMMENT_WIDTH, position);
				HPDF_Page_Stroke (page);
				
				if(comment){
					HPDF_Page_MoveTo (page, width - LR_MARGIN - COMMENT_WIDTH, position - CELL_HEIGHT);
					HPDF_Page_LineTo (page, width - LR_MARGIN - COMMENT_WIDTH, position);
					HPDF_Page_Stroke (page);
					if(j+1 == entries[i].ids.size()){
						tw = HPDF_Page_TextWidth (page, entries[i].comment.c_str());
						HPDF_Page_BeginText (page);
						HPDF_Page_TextRect(page, width - LR_MARGIN - COMMENT_WIDTH + 5, comment_startpos - 2, width - LR_MARGIN - 5, position + 2, entries[i].comment.c_str(), HPDF_TALIGN_LEFT, NULL);
						HPDF_Page_EndText (page);
					}
				}
				
				std::string idtext = entries[i].type + "/" + Wicher::Toolkit::itostr(entries[i].ids[j]);
				tw = HPDF_Page_TextWidth (page, idtext.c_str());
				HPDF_Page_BeginText (page);
				HPDF_Page_MoveTextPos (page, LR_MARGIN + 285 - COMMENT_WIDTH/2, position - (CELL_HEIGHT + CELL_HEADER_TEXT_SIZE)/2 + 1);
				//HPDF_Page_ShowText (page, entries[i].ids[j].c_str());
				HPDF_Page_ShowText (page, idtext.c_str());
				HPDF_Page_EndText (page);
				HPDF_Page_MoveTo (page, LR_MARGIN + 280 - COMMENT_WIDTH/2, position - CELL_HEIGHT);
				HPDF_Page_LineTo (page, LR_MARGIN + 280 - COMMENT_WIDTH/2, position);
				HPDF_Page_Stroke (page);
				position -= CELL_HEIGHT;
				
				if(position - CELL_HEIGHT < LR_MARGIN && j+1 != entries[i].ids.size()){
					HPDF_Page_SetFontAndSize (page, def_font, 10);
					HPDF_Page_BeginText (page);
					sprintf(buf, "Strona %d", page_n);
					tw = HPDF_Page_TextWidth (page, buf);
					HPDF_Page_TextOut (page, (width - tw)/2, UD_MARGIN/2, buf);
					HPDF_Page_EndText (page);
					++page_n;
					
					HPDF_Page_MoveTo (page, LR_MARGIN, position);
					HPDF_Page_LineTo (page, width - LR_MARGIN, position);
					HPDF_Page_Stroke (page);
					
					page = HPDF_AddPage(pdf);
					HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
					HPDF_Page_SetFontAndSize (page, def_font, CELL_HEADER_TEXT_SIZE);
					width = HPDF_Page_GetWidth(page);
					height = HPDF_Page_GetHeight(page);
					position = height - UD_MARGIN;
					HPDF_Page_SetLineWidth (page, 0.5);
					HPDF_Page_MoveTo (page, LR_MARGIN, position);
					HPDF_Page_LineTo (page, width - LR_MARGIN, position);
					HPDF_Page_Stroke (page);
				}
			}
			
			sprintf(buf, "%lu", entries[i].ids.size());
			tw = HPDF_Page_TextWidth (page, buf);
			HPDF_Page_BeginText (page);
			HPDF_Page_MoveTextPos (page, width - LR_MARGIN - COMMENT_WIDTH - 5 - tw, position - (CELL_HEIGHT + CELL_TEXT_SIZE)/2 + 1 + CELL_HEIGHT);
			HPDF_Page_ShowText (page, buf);
			HPDF_Page_EndText (page);
			
			HPDF_Page_MoveTo (page, LR_MARGIN, position);
			HPDF_Page_LineTo (page, width - LR_MARGIN, position);
			HPDF_Page_Stroke (page);
		}
		HPDF_Page_SetLineWidth (page, 1);
		HPDF_Page_MoveTo (page, LR_MARGIN, position);
		HPDF_Page_LineTo (page, width - LR_MARGIN, position);
		HPDF_Page_Stroke (page);
		
		if(position - 100 < LR_MARGIN){
			HPDF_Page_SetFontAndSize (page, def_font, 10);
			HPDF_Page_BeginText (page);
			sprintf(buf, "Strona %d", page_n);
			tw = HPDF_Page_TextWidth (page, buf);
			HPDF_Page_TextOut (page, (width - tw)/2, UD_MARGIN/2, buf);
			HPDF_Page_EndText (page);
			++page_n;
			
			page = HPDF_AddPage(pdf);
			HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
			HPDF_Page_SetFontAndSize (page, def_font, CELL_HEADER_TEXT_SIZE);
			width = HPDF_Page_GetWidth(page);
			height = HPDF_Page_GetHeight(page);
			position = height - UD_MARGIN;
		}
		
		/* Miejsce na podpis */
		HPDF_Page_MoveTo (page, 1.5*LR_MARGIN, position - 100);
		HPDF_Page_LineTo (page, 5.5*LR_MARGIN, position - 100);
		HPDF_Page_MoveTo (page, width - 1.5*LR_MARGIN, position - 100);
		HPDF_Page_LineTo (page, width - 5.5*LR_MARGIN, position - 100);
		HPDF_Page_Stroke (page);
		
		HPDF_Page_SetFontAndSize (page, def_font, 7);
		HPDF_Page_BeginText (page);
		HPDF_Page_TextOut (page, 3.5*LR_MARGIN, position - 110, "(data, pieczęć i/lub podpis)");
		HPDF_Page_TextOut (page, width - 3.5*LR_MARGIN, position - 110, "(data, pieczęć i/lub podpis)");
		HPDF_Page_EndText (page);
		
		HPDF_Page_SetFontAndSize (page, def_font, 10);
		HPDF_Page_BeginText (page);
		sprintf(buf, "Strona %d", page_n);
		tw = HPDF_Page_TextWidth (page, buf);
		HPDF_Page_TextOut (page, (width - tw)/2, UD_MARGIN/2, buf);
		HPDF_Page_EndText (page);

		/* do page description processes (do not have to check function return codes) */
		HPDF_SaveToFile (pdf, outname.c_str());
	} catch (...) {
		HPDF_Free (pdf);
		return false;
	}

	HPDF_Free (pdf);
	return true;
}
