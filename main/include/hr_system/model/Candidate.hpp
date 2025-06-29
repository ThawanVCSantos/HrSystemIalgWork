#ifndef RH_SYSTEM_MODEL_CANDIDATE_HPP
#define RH_SYSTEM_MODEL_CANDIDATE_HPP

#include "../../../../libs/binary_data/include/binary/data/BinaryEntity.hpp"

using binary::data::BinaryEntity;

namespace hr_system {
  namespace model {
    class Candidate : public BinaryEntity<Candidate> {
      private:
        char fullName[1100];
        int age;
        char cpf[15];
        char workSector[100];
        char position[100];
        char contractType[30];
        float salaryExpectation;
        bool isReferral;
        int yearsOfExperience;
      public:
        Candidate();
        Candidate(
          char fullName[1100], int age, char cpf[15], char workSector[100], char position[100], char contractType[30],
          float salaryExpectation, bool isReferral, int yearsOfExperience
        );

        const char* getFullName() const;
        void setFullName(char fullName[1100]);

        int getAge() const;
        void setAge(int age);

        const char* getCpf() const;
        void setCpf(char cpf[15]);

        const char* getWorkSector() const;
        void setWorkSector(char workSector[100]);

        const char* getPosition() const;
        void setPosition(char position[100]);

        const char* getContractType() const;
        void setContractType(char contractType[30]);

        float getSalaryExpectation() const;
        void setSalaryExpectation(float salaryExpectation);

        bool getIsReferral() const;
        void setIsReferral(bool isReferral);

        int getYearsOfExperience() const;
        void setYearsOfExperience(int yearsOfExperience);

        bool operator==(const Candidate& other) const;

        static const char* entityName();
    };
  }
}

#endif
