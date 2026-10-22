#include "engine.hpp"
#include <algorithm>
#include <cctype>

namespace Mackayla {

    SimulatorEngine::SimulatorEngine() {
        initialize_matrices();
    }

    SimulatorEngine::~SimulatorEngine() {}

    void SimulatorEngine::initialize_matrices() {
        evasion_keywords = { 
            "listen", "honestly", "reframe", "point is", "believe me", "to be fair", 
            "let's be real", "truely", "essentially", "basically", "exaggerating", 
            "missed the point", "unimportant", "moving on", "whatever", "look who is talking", 
            "you missed the point", "that is irrelevant", "let's change the subject", 
            "i'm not arguing about this", "it's not that deep", "you are making a big deal", 
            "don't make this about" 
        };
        fallacy_keywords = { 
            "always", "never", "everyone", "nobody", "obviously", "clearly", 
            "completely", "totally", "impossible", "perfectly", "ruined", "destroyed", 
            "all the time", "anyways", "undeniably", "either you are with me", 
            "everyone knows that", "it has always been", "there is no alternative", 
            "you are missing the factual", "it is common sense", "without a shadow of doubt", 
            "purely black and white" 
        };
        emotional_keywords = { 
            "trust", "blame", "fault", "hurt", "deserve", "regret", 
            "guilty", "fair", "selfish", "ungrateful", "disappointed", "crazy", 
            "paranoid", "overreacting", "heartless", "i never said that", 
            "you are remembering it wrong", "you are making things up", "if you actually cared", 
            "after everything i have done", "how can you say that", "you are twisting my words", 
            "i was only trying to help" 
        };
        // Explicit word tracking mapping hostile verbal escalations
        explicit_keywords = {
            "fuck", "shit", "bitch", "asshole", "dick", 
            "bastard", "idiot", "stupid", "hate", "pathetic"
        };
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
        int aggressive_score = 0;

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

        // Scan for Aggressive Escalation vectors
        for (const auto& word : explicit_keywords) {
            if (processed_text.find(word) != std::string::npos) {
                aggressive_score += 35;
                result.emotional_load_score += 15; // Hostility compounds emotional leverage vectors
                result.detected_patterns.push_back("AG_VEC: [" + word + "]");
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

        if (aggressive_score > 0) {
            result.primary_vector += "\n[ALERT: ACTIVE HOSTILITY ESCALATION DETECTED // METRIC STACK: " + std::to_string(aggressive_score) + "%]";
        }

        return result;
    }

} // namespace Mackayla

