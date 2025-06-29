#ifndef HR_SYSTEM_MENU_MENU_HPP
#define HR_SYSTEM_MENU_MENU_HPP

#include "../model/Candidate.hpp"
#include "../repository/CandidateRepository.hpp"
#include "enum/MenuListModeEnum.hpp"
#include "enum/HrMenuFieldEnum.hpp"
#include "../enum/OrderDirectionEnum.hpp"
#include "../../../../libs/util/include/util/ArrayList.hpp"
#include <string>

using hr_system::model::Candidate;
using hr_system::repository::CandidateRepository;
using util::ArrayList;
using hr_system::menu::enum_class::HrMenuFieldEnum;
using hr_system::enum_class::OrderDirectionEnum;
using hr_system::menu::enum_class::MenuListModeEnum;

namespace hr_system {
  namespace menu {

    class Menu {
      private:
        static const char* RESET;
        static const char* BOLD;
        static const char* RED;
        static const char* GREEN;
        static const char* YELLOW;
        static const char* BLUE;
        static const char* CYAN;

        CandidateRepository repository;
        ArrayList<Candidate> candidates;
        ArrayList<Candidate> candidatesView;
        MenuListModeEnum mode = MenuListModeEnum::PAGINATED;
        HrMenuFieldEnum orderByField = HrMenuFieldEnum::FULL_NAME;
        OrderDirectionEnum orderByDirection = OrderDirectionEnum::ASC;
        int itemsPerPage = 10;
        int currentPage = 1;
        int totalPages = 1;
        bool started = false;

        void printListHeader();

        void goToNextPage();
        void goToPrevPage();

        bool canGoToNextPage();
        bool canGoToPrevPage();

        void print();

        void printHeader();

        void printList();

        void printOptions();

        void printDivider(char c = '-', bool isBold = true, std::string color = "\033[33m", int size = 143, bool hasBreakLine = true);
        void printHeaderSelectOption();
        void printHeaderSelectOptionOrderBy();
        void printOptionsDirectionOrderBy(HrMenuFieldEnum field);
        void printHeaderDirectionOrderBy();
        void printHeaderFindBy();

        void addCandidate();

        void printPagination();

        void removeCandidate();

        void toggleListMode();

        void selectOption();
        void importCsv();
        void exportCsv();

        void applyOrderBy();
        void selectOptionOrderBy();
        HrMenuFieldEnum getFieldOrderByOption(int option);
        HrMenuFieldEnum getFieldFindOption(int option);
        OrderDirectionEnum getFieldOrderDirectionOption(int option);
        void selectDirectionOrderBy(HrMenuFieldEnum field);
        void selectOptionFindBy();
        void printOptionsFindBy();

        void printOptionsOrderBy();

        void defineItemsPerPage();

        void updateCandidatesView();
        void save();
        void waitForEnter();

      public:
        void start();
    };
  }
}

#endif
