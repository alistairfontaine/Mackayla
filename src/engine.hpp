#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>
#include <vector>

namespace Mackayla {

    // Defines the metrics for our manipulation payload calculation
    struct AnalysisResult {
        int evasion_score;
        int logical_fallacy_score;
        int emotional_load_score;
        std::string primary_vector;
        std::vector<std::string> detected_patterns;
    };

    class SimulatorEngine {
    private:
        // First-principles evaluation rules
        std::vector<std::string> evasion_keywords;
        std::vector<std::string> fallacy_keywords;
        std::vector<std::string> emotional_keywords;
        std::vector<std::string> explicit_keywords; // Added tracking variable link

        void initialize_matrices();

    public:
        SimulatorEngine();
        ~SimulatorEngine();

        // Core analysis pipeline
        AnalysisResult evaluate_text(const std::string& input_text);
    };

} // namespace Mackayla

#endif // ENGINE_HPP

