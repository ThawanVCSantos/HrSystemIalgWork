#ifndef RH_SYSTEM_REPOSITORY_CANDIDATE_REPOSITORY_HPP
#define RH_SYSTEM_REPOSITORY_CANDIDATE_REPOSITORY_HPP

#include "../../../../libs/binary_data/include/binary/data/BinaryFileRepository.hpp"
#include "../model/Candidate.hpp"

using binary::data::BinaryFileRepository;

namespace hr_system {
  namespace repository {
    class CandidateRepository : public BinaryFileRepository<model::Candidate> {
    };
  }
}

#endif
