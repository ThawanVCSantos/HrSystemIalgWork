#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <limits>

#include "../../include/hr_system/model/Candidate.hpp"
#include "../../include/hr_system/repository/CandidateRepository.hpp"
#include "../../include/hr_system/menu/Menu.hpp"
#include "../../include/hr_system/menu/enum/HrMenuFieldEnum.hpp"
#include "../../include/hr_system/enum/OrderDirectionEnum.hpp"
#include "../../include/hr_system/menu/enum/MenuListModeEnum.hpp"
#include "../../../libs/util/include/util/ArrayList.hpp"

using hr_system::menu::Menu;
using hr_system::menu::enum_class::MenuListModeEnum;
using util::StringUtils;

using hr_system::menu::enum_class::HrMenuFieldEnum;
using hr_system::enum_class::OrderDirectionEnum;
using hr_system::repository::CandidateRepository;

const char* hr_system::menu::Menu::RESET = "\033[0m";
const char* hr_system::menu::Menu::BOLD = "\033[1m";
const char* hr_system::menu::Menu::RED = "\033[31m";
const char* hr_system::menu::Menu::GREEN = "\033[32m";
const char* hr_system::menu::Menu::YELLOW = "\033[33m";
const char* hr_system::menu::Menu::BLUE = "\033[34m";
const char* hr_system::menu::Menu::CYAN = "\033[36m";

void Menu::waitForEnter() {
  std::cout << YELLOW << "Pressione Enter para continuar..." << RESET << std::endl;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::start() {;
  started = true;
  candidates = repository.readAll();
  updateCandidatesView();
  while (started) {
    print();
    selectOption();
  }
}

void Menu::print() {
  printHeader();
  printDivider();
  printList();
  printDivider();
  if(mode == MenuListModeEnum::PAGINATED) {
    printPagination();
  }
  std::cout << std::endl;
  printOptions();
}

void Menu::printHeader() {
  std::cout << BOLD << BLUE << std::string(59, '=')
    << " Recrutamento e Seleção "
    << std::string(60, '=') << RESET << std::endl;
}

void Menu::printListHeader() {
  std::cout << BOLD << YELLOW << "| " << RESET
    << BOLD << StringUtils::centralize("Nome", 30)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("Idade", 5)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("CPF", 14)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("Setor", 18)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("Cargo", 18)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("Contrato", 13)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("P. Salarial", 11)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("Ind", 3)
    << BOLD << YELLOW << " | " << RESET << BOLD << StringUtils::centralize("Exp", 3)
    << BOLD << YELLOW << " |" << RESET << std::endl;
}

void Menu::printList() {

  printListHeader();
  printDivider();
  if (candidatesView.isEmpty()) {
    std::cout << BOLD << YELLOW << '|' << RESET << std::setw(56) << "" << RED << "Nenhum candidato cadastrado." << RESET << std::setw(56) << "" << BOLD << YELLOW << '|' << RESET << std::endl;
  } else {
    candidatesView.forEach([this](Candidate c, int index) {
      std::cout << YELLOW << "| " << RESET << std::setw(30) << std::left << StringUtils::truncate(c.getFullName(), 30)
        << YELLOW << " | " << RESET << std::setw(5)  << c.getAge()
        << YELLOW << " | " << RESET << std::setw(14) << c.getCpf()
        << YELLOW << " | " << RESET << std::setw(18) << StringUtils::truncate(c.getWorkSector(), 18)
        << YELLOW << " | " << RESET << std::setw(18) << StringUtils::truncate(c.getPosition(), 18)
        << YELLOW << " | " << RESET << std::setw(13) << StringUtils::truncate(c.getContractType(), 13)
        << YELLOW << " | " << RESET << std::setw(11) << std::fixed << std::setprecision(2) << c.getSalaryExpectation()
        << YELLOW << " | " << RESET << std::setw(3)  << (c.getIsReferral() ? "Sim" : "Nao")
        << YELLOW << " | " << RESET << std::setw(3)  << c.getYearsOfExperience()
        << YELLOW << " |" << RESET << std::endl;
        if(index < candidatesView.size() - 1) {
          this->printDivider('.', false);
        }
    });
  }
}

void Menu::printHeaderSelectOption() {
  std::cout << CYAN << BOLD << "+";
  printDivider('-', true, CYAN, 60, false);
  std::cout << CYAN << BOLD << " Selecione uma Opção ";
  printDivider('-', true, CYAN, 60, false);
  std::cout << CYAN << BOLD << "+" << RESET << std::endl;
}

void Menu::printHeaderSelectOptionOrderBy() {
  std::cout << CYAN << BOLD << "+";
  printDivider('-', true, CYAN, 64, false);
  std::cout << CYAN << BOLD << " Ordenar por ";
  printDivider('-', true, CYAN, 64, false);
  std::cout << CYAN << BOLD << "+" << RESET << std::endl;
}

void Menu::printHeaderFindBy() {
  std::cout << CYAN << BOLD << "+";
  printDivider('-', true, CYAN, 64, false);
  std::cout << CYAN << BOLD << " Buscar por ";
  printDivider('-', true, CYAN, 65, false);
  std::cout << CYAN << BOLD << "+" << RESET << std::endl;
}

void Menu::printOptions() {
  printHeaderSelectOption();

  std::cout << CYAN << "|" << RESET
    << " 👥 Candidatos:" << std::setw(4) << ""
    << "1. Adicionar" << std::setw(9) << ""
    << "2. Remover" << std::setw(91) << ""
    << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << "|" << RESET << std::string(141, ' ') << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << "|" << RESET
    << " 📄 Arquivo:" << std::setw(7) << ""
    << "3. Importar CSV" << std::setw(6) << ""
    << "4. Exportar CSV" << std::setw(86) << ""
    << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << "|" << RESET << std::string(141, ' ') << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << "|" << RESET
    << " 🔍 Visualização:  "
    << "5. Ordenar por:" << std::setw(6) << ""
    << "6. Buscar por:" << std::setw(7) << ""
    << "7. Visualizar Lista " << (mode == MenuListModeEnum::PAGINATED ? "Completa" : "Paginada") << std::setw(5) << ""
    << (mode == MenuListModeEnum::PAGINATED ? "8. Definir items/página" : "") << std::setw(mode == MenuListModeEnum::PAGINATED ? 24 : 47) << ""
    << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << "|" << RESET << std::string(141, ' ') << CYAN << "|" << RESET << std::endl;

  if (mode == MenuListModeEnum::PAGINATED && totalPages > 1) {
    std::cout << CYAN << "|" << RESET
      << " 🧭 Navegação:" << std::setw(5) << "";
    int space = 84;
    if(canGoToPrevPage()) {
      std::cout << "b. Página anterior" << std::setw(3) << "";
    } else {
      space += 21;
    }
    if(canGoToNextPage()) {
      std::cout << "n. Próxima página";
    } else {
      space += 17;
    }
    std::cout << std::setw(space) << "";
    std::cout << CYAN << "|" << RESET << std::endl;

    std::cout << CYAN << "|" << RESET << std::string(141, ' ') << CYAN << "|" << RESET << std::endl;
  }

  std::cout << CYAN << "|" << RESET
    << " 🚪 Sistema:" << std::setw(7) << ""
    << GREEN << "s. Salvar" << RESET << std::setw(12) << ""
    << RED << "0. Sair" << RESET << std::setw(94) << ""
    << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << BOLD << "+" << std::string(141, '-') << "+" << RESET << std::endl;
  std::cout << CYAN << BOLD << "-> " << RESET;
}

void Menu::printHeaderDirectionOrderBy() {
  std::cout << CYAN << BOLD << "+";
  printDivider('-', true, CYAN, 66, false);
  std::cout << CYAN << BOLD << " Direção ";
  printDivider('-', true, CYAN, 66, false);
  std::cout << CYAN << BOLD << "+" << RESET << std::endl;
}

void Menu::printOptionsDirectionOrderBy(HrMenuFieldEnum field) {
  printHeaderDirectionOrderBy();

  std::cout << CYAN << "|" << RESET << (field == HrMenuFieldEnum::IS_REFERRAL ? " 1. Não Indicado" : " 1. Crescente") << std::setw(5) << ""
    << (field == HrMenuFieldEnum::IS_REFERRAL ? "2. Indicado" : "2. Decrescente") << YELLOW << std::setw(5) << ""
    << "0. Voltar" << std::setw(100) << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << BOLD << "+" << std::string(141, '-') << "+" << RESET << std::endl;
  std::cout << CYAN << BOLD << "-> " << RESET;
}

void Menu::printPagination() {
  if (mode == MenuListModeEnum::PAGINATED) {
    std::cout << CYAN << std::setw(63) << "" << "< Página " << currentPage << " de " << totalPages << " >" << RESET << std::endl;
  }
}

void Menu::printDivider(char c, bool isBold, std::string color, int size, bool hasBreakLine) {
  if(isBold) {
    std::cout << BOLD;
  }
  std::cout << color << std::string(size, c) << RESET;
  if(hasBreakLine) {
    std::cout << std::endl;
  }
}

void Menu::updateCandidatesView() {
  this->candidatesView = this->candidates;
  applyOrderBy();
  if(mode == MenuListModeEnum::PAGINATED && this->candidatesView.size() > 0) {
    totalPages = std::max(1, (int)std::ceil((double)candidates.size() / itemsPerPage));
    int start = (currentPage - 1) * itemsPerPage;
    int end = std::min(start + itemsPerPage, candidatesView.size());
    ArrayList<Candidate> aux;
    for (int i = start; i < end; i++) {
      aux.add(candidatesView.get(i));
    }
    this->candidatesView = aux;
  }
}

void Menu::goToNextPage() {
  if(!canGoToNextPage()) {
    return;
  }
  currentPage++;
  updateCandidatesView();
}

void Menu::goToPrevPage() {
  if(!canGoToPrevPage()) {
    return;
  };
  currentPage--;
  updateCandidatesView();
}

bool Menu::canGoToNextPage() {
  if(mode != MenuListModeEnum::PAGINATED || currentPage == totalPages) {
    return false;
  }
  return true;
}

bool Menu::canGoToPrevPage() {
  if(mode != MenuListModeEnum::PAGINATED || currentPage == 1) {
    return false;
  }
  return true;
}

void Menu::addCandidate() {
  char fullNameAux[1100], cpfAux[15], workSectorAux[100], positionAux[100], ContractTypeAux[30], referralResponseAux;
  int ageAux, yearOfExperienceAux;
  double salaryExpectationAux;
  bool isReferralAux, isValidInput = false;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << CYAN << "Digite o nome completo do candidato: " << RESET;
	std::cin.getline(fullNameAux, 1100);

  while (!isValidInput) {
	  std::cout << CYAN << "Digite a idade do candidato: " << RESET;
    if(std::cin >> ageAux) {
      if(ageAux > 0) {
        isValidInput = true;
      } else {
        std::cout << std::endl << RED << "Idade deve ser maior que zero!" << RESET << std::endl << std::endl;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl << RED << "Entrada inválida! Digite um número inteiro positivo." << RESET << std::endl << std::endl;
    }
  }
	std::cin.ignore();

	std::cout << CYAN << "Digite o CPF formatado do candidato: " << RESET;
	std::cin.getline(cpfAux, 15);

	std::cout << CYAN << "Digite o setor de trabalho do candidato: " << RESET;
	std::cin.getline(workSectorAux, 100);

	std::cout << CYAN << "Digite o cargo do candidato: " << RESET;
	std::cin.getline(positionAux, 100);

	std::cout << CYAN << "Digite o tipo de contrato: " << RESET;
	std::cin.getline(ContractTypeAux, 30);

  isValidInput = false;

  while (!isValidInput) {
	  std::cout << CYAN << "Digite a pretensão salarial: " << RESET;
    if(std::cin >> salaryExpectationAux) {
      if(salaryExpectationAux > 0) {
        isValidInput = true;
      } else {
        std::cout << std::endl << RED << "Pretensão salarial deve ser maior ou igual a zero!" << RESET << std::endl << std::endl;
      }
      isValidInput = true;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl << RED << "Entrada inválida! Digite um número positivo." << RESET << std::endl << std::endl;
    }
  }
	std::cin.ignore();

	std::cout << CYAN << "O candidato foi indicado? [s/N]: " << RESET;
	std::cin >> referralResponseAux;
	std::cin.ignore();

  isReferralAux = StringUtils::toLowerCase(referralResponseAux) == 's';

  isValidInput = false;

  while (!isValidInput) {
	  std::cout << CYAN << "Quantos anos de experiência o candidato possui?: " << RESET;
    if(std::cin >> yearOfExperienceAux && yearOfExperienceAux >= 0) {
      isValidInput = true;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl << RED << "Entrada inválida! Digite um número maior ou igual a zero" << RESET << std::endl << std::endl;
    }
  }
	std::cin.ignore();

  Candidate novoCandidato(
    fullNameAux, ageAux, cpfAux, workSectorAux, positionAux,
    ContractTypeAux, salaryExpectationAux, isReferralAux, yearOfExperienceAux
  );

  candidates.add(novoCandidato);

  std::cout << GREEN << "\nCandidato adicionado com sucesso!" << RESET << std::endl << std::endl;
  waitForEnter();

  updateCandidatesView();
}

void Menu::removeCandidate() {
  char cpf[15];
  std::cout << CYAN << "Qual candidato deseja remover? (Digite o CPF do candidato): " << RESET;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.getline(cpf, 15);
  const Candidate* candidate = candidates.findBy(std::string(cpf), [](Candidate c) {
    return c.getCpf();
  });

  std::cout << std::endl;

  if(candidate != nullptr) {
    candidates.remove(candidate);
    std::cout << GREEN << "Candidato excluido com sucesso!"  << RESET << std::endl;
  } else {
    std::cout << RED << "Candidato nao encontrado!" << RESET << std::endl;
  }
  std::cout << std::endl;
  waitForEnter();
  updateCandidatesView();
}

void Menu::toggleListMode() {
  if(mode == MenuListModeEnum::ALL) {
    mode = MenuListModeEnum::PAGINATED;
    currentPage = 1;
  } else {
    mode = MenuListModeEnum::ALL;
  }
  updateCandidatesView();
}

void Menu::importCsv() {

  std::string filePath;
  std::cout << CYAN << "Digite o caminho do arquivo CSV: " << RESET;
  std::cin >> filePath;

  char aux;

  std::cout << CYAN << "Deseja limpar os itens atuais? [s/N]: " << RESET;
  std::cin >> aux;
  std::cin.ignore();

  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
    return;
  }

  if(StringUtils::toLowerCase(aux) == 's') {
    candidates.clear();
  }

  std::string linha;

  std::getline(file, linha);

  while (std::getline(file, linha)) {
    std::istringstream ss(linha);
    std::string field;

    Candidate c;

    std::getline(ss, field, ';');
    c.setFullName(const_cast<char*>(field.c_str()));

    std::getline(ss, field, ';');
    c.setAge(std::stoi(field));

    std::getline(ss, field, ';');
    c.setCpf(const_cast<char*>(field.c_str()));

    std::getline(ss, field, ';');
    c.setWorkSector(const_cast<char*>(field.c_str()));

    std::getline(ss, field, ';');
    c.setPosition(const_cast<char*>(field.c_str()));

    std::getline(ss, field, ';');
    c.setContractType(const_cast<char*>(field.c_str()));

    std::getline(ss, field, ';');
    c.setSalaryExpectation(!field.empty() ? std::stof(field) : 0);

    std::getline(ss, field, ';');
    c.setIsReferral(field == "1" || field == "true");

    std::getline(ss, field, ';');
    c.setYearsOfExperience(!field.empty() ? std::stoi(field) : 0);

    candidates.add(c);
  }

  file.close();

  std::cout << GREEN << "\nCandidatos importados com sucesso!\n\n" << RESET;
  waitForEnter();

  updateCandidatesView();
}

void Menu::exportCsv() {
  std::string filePath;
  std::cout << CYAN << "Digite o caminho do arquivo CSV: " << RESET;
  std::cin >> filePath;
  std::ofstream file(filePath);

  if (!file.is_open()) {
    std::cerr << RED << "Erro ao abrir o arquivo para escrita!" << RESET << std::endl;
    return;
  }

  file << "Nome Completo,Idade,CPF,Setor de Trabalho,Cargo,Tipo de Contrato,Pretensão Salarial,Indicacao,Ano de Experiencia\n";

  candidatesView.forEach([&file](Candidate c) {
    file << c.getFullName() << ";"
      << c.getAge() << ";"
      << c.getCpf() << ";"
      << c.getWorkSector() << ";"
      << c.getPosition() << ";"
      << c.getContractType() << ";"
      << c.getSalaryExpectation() << ";"
      << (c.getIsReferral()) << ";"
      << c.getYearsOfExperience() << "\n";
  });

  file.close();

  std::cout << std::endl << GREEN << "Candidatos exportados com sucesso!" << RESET << std::endl << std::endl;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  waitForEnter();
}

void Menu::defineItemsPerPage() {
  int itemsPerPageAux;
  bool isValidInput = false;

  while (!isValidInput) {
    std::cout << CYAN << "Digite a quantidade de itens por página: " << RESET;

    if (std::cin >> itemsPerPageAux) {
      if (itemsPerPageAux > 0) {
        isValidInput = true;
      } else {
        std::cout << std::endl << RED << "Quantidade deve ser maior que zero!" << RESET << std::endl << std::endl;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl << RED << "Entrada inválida! Digite um número inteiro positivo." << RESET << std::endl << std::endl;
    }
  }

  itemsPerPage = itemsPerPageAux;
  updateCandidatesView();
}

void Menu::printOptionsOrderBy() {
  printHeaderSelectOptionOrderBy();

  std::cout << CYAN << "|" << RESET << " 1. Nome Completo" << std::setw(5) << ""
    << "2. Idade" << std::setw(5) << ""
    << "3. CPF" << std::setw(5) << ""
    << "4. Setor" << std::setw(5) << ""
    << "5. Cargo" << std::setw(5) << ""
    << "6. Tipo de Contrato" << std::setw(55) << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << "|" << RESET << std::string(141, ' ') << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << "|" << RESET << " 7. Pretensão Salarial" << std::setw(5) << ""
    << "8. Indicação" << std::setw(5) << ""
    << "9. Anos de Experiência" << std::setw(5) << ""
    << YELLOW << "0. Voltar" << std::setw(61) << ""
    << CYAN << "|" << RESET << std::endl;


  std::cout << CYAN << BOLD << "+" << std::string(141, '-') << "+" << RESET << std::endl;
  std::cout << CYAN << BOLD << "-> " << RESET;
}

HrMenuFieldEnum Menu::getFieldOrderByOption(int option) {
  switch (option) {
    case 1:
      return HrMenuFieldEnum::FULL_NAME;
    case 2:
      return HrMenuFieldEnum::AGE;
    case 3:
      return HrMenuFieldEnum::CPF;
    case 4:
      return HrMenuFieldEnum::WORK_SECTOR;
    case 5:
      return HrMenuFieldEnum::POSITION;
    case 6:
      return HrMenuFieldEnum::CONTRACT_TYPE;
    case 7:
      return HrMenuFieldEnum::SALARY_EXPECTATION;
    case 8:
      return HrMenuFieldEnum::IS_REFERRAL;
    case 9:
      return HrMenuFieldEnum::YEARS_OF_EXPERIENCE;
    default:
      return HrMenuFieldEnum::FULL_NAME;
  }
}

void Menu::selectOptionOrderBy() {
  printOptionsOrderBy();

  bool isValidInput = false;
  int option;

  while (!isValidInput) {
    if(std::cin >> option) {
      if(option < 0 || option > 9) {
        std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
        std::cout << CYAN << "Digite novamente: " << RESET;
      } else {
        isValidInput = true;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
      std::cout << CYAN << "Digite novamente: " << RESET;
    }
  }

  if (option == 0) return;

  HrMenuFieldEnum fieldToOrder = getFieldOrderByOption(option);

  selectDirectionOrderBy(fieldToOrder);
}

void Menu::printOptionsFindBy() {
  printHeaderFindBy();

  std::cout << CYAN << "|" << RESET << " 1. Nome Completo" << std::setw(5) << ""
    << "2. CPF" << YELLOW << std::setw(5) << ""
    << "0. Voltar" << std::setw(5) << ""
    << std::setw(94) << "" << CYAN << "|" << RESET << std::endl;

  std::cout << CYAN << BOLD << "+" << std::string(141, '-') << "+" << RESET << std::endl;
  std::cout << CYAN << BOLD << "-> " << RESET;
}

HrMenuFieldEnum Menu::getFieldFindOption(int option) {
  switch (option) {
    case 1:
      return HrMenuFieldEnum::FULL_NAME;
    case 2:
      return HrMenuFieldEnum::CPF;
    default:
      return HrMenuFieldEnum::FULL_NAME;
  }
}

void Menu::selectOptionFindBy() {
  printOptionsFindBy();

  bool isValidInput = false;
  int option;

  while (!isValidInput) {
    if(std::cin >> option) {
      if(option < 0 || option > 2) {
        std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
        std::cout << CYAN << "Digite novamente: " << RESET;
      } else {
        isValidInput = true;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
      std::cout << CYAN << "Digite novamente: " << RESET;
    }
  }

  if(option == 0) return;

  HrMenuFieldEnum fieldToFind = getFieldFindOption(option);

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::string aux;
  std::cout << CYAN <<  "Digite o " << (fieldToFind == HrMenuFieldEnum::FULL_NAME ? "nome completo" : "CPF") << " do candidato: " << RESET;
  std::getline(std::cin, aux);

  std::cout << (fieldToFind == HrMenuFieldEnum::FULL_NAME ? "Nome completo: " : "CPF: ") << aux << std::endl;

  const Candidate* candidate = candidates.findBy(aux, [&fieldToFind](Candidate c) {
    return fieldToFind == HrMenuFieldEnum::FULL_NAME ? c.getFullName() : c.getCpf();
  });

  std::cout << std::endl;
  printDivider();
  if(candidate != nullptr) {
    std::cout << GREEN << "Nome completo: " << RESET << candidate->getFullName() << RESET << std::endl;
    std::cout << GREEN << "Idade: " << RESET << candidate->getAge() << RESET << std::endl;
    std::cout << GREEN << "CPF: " << RESET << candidate->getCpf() << RESET << std::endl;
    std::cout << GREEN << "Setor de trabalho: " << RESET << candidate->getWorkSector() << RESET << std::endl;
    std::cout << GREEN << "Cargo: " << RESET << candidate->getPosition() << RESET << std::endl;
    std::cout << GREEN << "Tipo de contrato: " << RESET << candidate->getContractType() << RESET << std::endl;
    std::cout << GREEN << "Pretensão salarial: " << RESET << candidate->getSalaryExpectation() << RESET << std::endl;
    std::cout << GREEN << "Indicacao: " << RESET << (candidate->getIsReferral() ? "Sim" : "Nao") << RESET << std::endl;
    std::cout << GREEN << "Ano de experiencia: " << RESET << candidate->getYearsOfExperience() << RESET << std::endl;
  } else {
    std::cout << RED << "Nenhum candidato encontrado" << RESET << std::endl;
  }
  printDivider();

  std::cout << std::endl;

  waitForEnter();
}

void Menu::selectOption() {
  char option;

  std::cin >> option;

  switch (StringUtils::toLowerCase(option)) {
    case '1':
      addCandidate();
      break;
    case '2':
      removeCandidate();
      break;
    case '3':
      importCsv();
      break;
    case '4':
      exportCsv();
      break;
    case '5':
      selectOptionOrderBy();
      break;
    case '6':
      selectOptionFindBy();
      break;
    case '7':
      toggleListMode();
      break;
    case '8':
      defineItemsPerPage();
      break;
    case 'b':
      if(!canGoToPrevPage()) {
        std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        waitForEnter();
      } else {
        goToPrevPage();
      }
      break;
    case 'n':
      if(!canGoToNextPage()) {
        std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        waitForEnter();
      } else {
        goToNextPage();
      }
      break;
    case 's':
      save();
      break;
    case '0':
      started = false;
      std::cout << YELLOW << "\nEncerrando..." << RESET << std::endl << std::endl;
      break;
    default:
      std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      waitForEnter();
      break;
  }
}

void Menu::applyOrderBy() {
  if(this->orderByField == HrMenuFieldEnum::FULL_NAME) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getFullName()) < std::string(b.getFullName());
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getFullName()) > std::string(b.getFullName());
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::AGE) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getAge() < b.getAge();
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getAge() > b.getAge();
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::CPF) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getCpf()) < std::string(b.getCpf());
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getCpf()) > std::string(b.getCpf());
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::WORK_SECTOR) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getWorkSector()) < std::string(b.getWorkSector());
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getWorkSector()) > std::string(b.getWorkSector());
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::POSITION) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getPosition()) < std::string(b.getPosition());
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getPosition()) > std::string(b.getPosition());
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::CONTRACT_TYPE) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getContractType()) < std::string(b.getContractType());
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return std::string(a.getContractType()) > std::string(b.getContractType());
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::SALARY_EXPECTATION) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getSalaryExpectation() < b.getSalaryExpectation();
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getSalaryExpectation() > b.getSalaryExpectation();
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::IS_REFERRAL) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getIsReferral() < b.getIsReferral();
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getIsReferral() > b.getIsReferral();
      });
    }
  } else if(this->orderByField == HrMenuFieldEnum::YEARS_OF_EXPERIENCE) {
    if(this->orderByDirection == OrderDirectionEnum::ASC) {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getYearsOfExperience() < b.getYearsOfExperience();
      });
    } else {
      candidatesView = candidatesView.sort([](Candidate a, Candidate b) {
        return a.getYearsOfExperience() > b.getYearsOfExperience();
      });
    }
  }
}

OrderDirectionEnum Menu::getFieldOrderDirectionOption(int option) {
  switch (option) {
    case 1:
      return OrderDirectionEnum::ASC;
    case 2:
      return OrderDirectionEnum::DESC;
    default:
      return OrderDirectionEnum::ASC;
  }
}

void Menu::selectDirectionOrderBy(HrMenuFieldEnum field) {
  printOptionsDirectionOrderBy(field);

  bool isValidInput = false;
  int option;

  while (!isValidInput) {
    if(std::cin >> option) {
      if(option < 0 || option > 2) {
        std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
        std::cout << CYAN << "Digite novamente: " << RESET;
      } else {
        isValidInput = true;
      }
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << std::endl << RED << "Opção inválida!" << RESET << std::endl << std::endl;
      std::cout << CYAN << "Digite novamente: " << RESET;
    }
  }

  if (option == 0) return selectOptionOrderBy();

  OrderDirectionEnum direction = getFieldOrderDirectionOption(option);

  this->orderByField = field;
  this->orderByDirection = direction;
  updateCandidatesView();
}

void Menu::save() {
  repository.writeAll(this->candidates, true);
  std::cout << GREEN << "\nCandidatos salvos com sucesso!\n\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  waitForEnter();
}
