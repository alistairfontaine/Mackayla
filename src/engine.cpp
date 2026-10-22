#include "engine.hpp"
#include <algorithm>
#include <cctype>

namespace Mackayla {

    SimulatorEngine::SimulatorEngine() {
        initialize_matrices();
    }

    SimulatorEngine::~SimulatorEngine() {}

    void SimulatorEngine::initialize_matrices() {
        // Core structural vectors tracking specific manipulation signatures
        evasion_keywords = { "listen", "honestly", "reframe", "point is", "believe me", "to be fair", "let's be real", "truely", "essentially", "basically", "exaggerating", "missed the point", "unimportant", "moving on", "whatever" };
        fallacy_keywords = { "always", "never", "everyone", "nobody", "obviously", "clearly", "completely", "totally", "impossible", "perfectly", "ruined", "destroyed", "all the time", "anyways", "undeniably" };
        emotional_keywords = { "trust", "blame", "fault", "hurt", "deserve", "regret", "guilty", "fair", "selfish", "ungrateful", "disappointed", "crazy", "paranoid", "overreacting", "heartless" };
    }

    // Helper utility to convert a string to lowercase for exact token matching
    std::string to_lowercase(const std::string& str) {
        std::string lower_str = str;
        std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        return lower_str;
    }

    AnalysisResult SimulatorEngine::evaluate_text(const std::string& input_text) {
        AnalysisResult result{0, 0, 0, "UNDETERMINED", {}};
        std::string processed_text = to_lowercase(input_text);

        // Scan for Evasion vectors
        for (const auto& word : evasion_keywords) {
            if (processed_text.find(word) != std::string::npos) {
                result.evasion_score += 25;
                result.detected_patterns.push_back("EV_VEC: [" + word + "]");
            }
        }

        // Scan for Logical Fallacy vectors
        for (const auto& word : fallacy_keywords) {
            if (processed_text.find(word) != std::string::npos) {
                result.logical_fallacy_score += 25;
                result.detected_patterns.push_back("FL_VEC: [" + word + "]");
            }
        }

        // Scan for Emotional Load vectors
        for (const auto& word : emotional_keywords) {
            if (processed_text.find(word) != std::string::npos) {
                result.emotional_load_score += 25;
                result.detected_patterns.push_back("EM_VEC: [" + word + "]");
            }
        }

        // Determine dominant manipulation payload
        if (result.evasion_score >= result.logical_fallacy_score && result.evasion_score >= result.emotional_load_score && result.evasion_score > 0) {
            result.primary_vector = "TACTICAL_DEFLECTION";
        } else if (result.logical_fallacy_score >= result.evasion_score && result.logical_fallacy_score >= result.emotional_load_score && result.logical_fallacy_score > 0) {
            result.primary_vector = "RHETORICAL_CHALLENGE";
        } else if (result.emotional_load_score > 0) {
            result.primary_vector = "PSYCHOLOGICAL_LEVERAGE";
        }

        return result;
    }

} // namespace Mackayla

