#include "../../../libs/binary_data/include/binary/data/BinaryEntity.hpp"
#include "../../include/hr_system/model/Candidate.hpp"
#include "../../../libs/util/include/util/ArrayUtils.hpp"

#include <string>
#include <iostream>

using util::ArrayUtils;

namespace hr_system {
  namespace model {

    const char* Candidate::getFullName() const {
      return this->fullName;
    }

    void Candidate::setFullName(char fullName[1100]) {
      ArrayUtils::copyArrayElements(fullName, this->fullName, 1100);
    }

    int Candidate::getAge() const {
      return this->age;
    }

    void Candidate::setAge(int age) {
      this->age = age;
    }

    const char* Candidate::getCpf() const {
      return this->cpf;
    }

    void Candidate::setCpf(char cpf[15]) {
      ArrayUtils::copyArrayElements(cpf, this->cpf, 15);
    }

    const char* Candidate::getWorkSector() const {
      return this->workSector;
    }

    void Candidate::setWorkSector(char workSector[100]) {
      ArrayUtils::copyArrayElements(workSector, this->workSector, 100);
    }

    const char* Candidate::getPosition() const {
      return this->position;
    }

    void Candidate::setPosition(char position[100]) {
      ArrayUtils::copyArrayElements(position, this->position, 100);
    }

    const char* Candidate::getContractType() const {
      return this->contractType;
    }

    void Candidate::setContractType(char contractType[30]) {
      ArrayUtils::copyArrayElements(contractType, this->contractType, 30);
    }

    float Candidate::getSalaryExpectation() const {
      return this->salaryExpectation;
    }

    void Candidate::setSalaryExpectation(float salaryExpectation) {
      this->salaryExpectation = salaryExpectation;
    }

    bool Candidate::getIsReferral() const {
      return this->isReferral;
    }

    void Candidate::setIsReferral(bool isReferral) {
      this->isReferral = isReferral;
    }

    int Candidate::getYearsOfExperience() const {
      return this->yearsOfExperience;
    }

    void Candidate::setYearsOfExperience(int yearsOfExperience) {
      this->yearsOfExperience = yearsOfExperience;
    }

    const char* Candidate::entityName() {
      return "candidate";
    }

    bool Candidate::operator==(const Candidate& other) const {
      return std::string(this->cpf) == std::string(other.getCpf());
    }

    Candidate::Candidate() {}

    Candidate::Candidate(
      char fullName[1100], int age, char cpf[15], char workSector[100], char position[100], char contractType[30],
      float salaryExpectation, bool isReferral, int yearsOfExperience
    ) {
      ArrayUtils::copyArrayElements(fullName, this->fullName, 1100);
      ArrayUtils::copyArrayElements(cpf, this->cpf, 15);
      ArrayUtils::copyArrayElements(workSector, this->workSector, 100);
      ArrayUtils::copyArrayElements(position, this->position, 100);
      ArrayUtils::copyArrayElements(contractType, this->contractType, 30);
      this->age = age;
      this->salaryExpectation = salaryExpectation;
      this->isReferral = isReferral;
      this->yearsOfExperience = yearsOfExperience;
    }
  }
}
