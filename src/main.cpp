#include <iostream>
#include <string>
#include "engine.hpp"

// External linkage block ensuring function names are preserved when compiled to WebAssembly
extern "C" {

    // Main web evaluation interface endpoint
    const char* analyze_payload(const char* raw_input) {
        if (!raw_input) return "ERROR: EMPTY_PAYLOAD";

        static std::string report_buffer;
        report_buffer.clear();

        Mackayla::SimulatorEngine engine;
        Mackayla::AnalysisResult result = engine.evaluate_text(std::string(raw_input));

        // Assemble the intelligence telemetry readout string
        report_buffer += "--------------------------------------------------\n";
        report_buffer += "MACKAYLA // INTERCEPT METRIC TELEMETRY LOGS\n";
        report_buffer += "--------------------------------------------------\n";
        report_buffer += "DOMINANT THREAT VECTOR : " + result.primary_vector + "\n";
        report_buffer += "TACTICAL DEFLECTION    : " + std::to_string(result.evasion_score) + "%\n";
        report_buffer += "RHETORICAL CHALLENGE   : " + std::to_string(result.logical_fallacy_score) + "%\n";
        report_buffer += "PSYCHOLOGICAL LEVERAGE : " + std::to_string(result.emotional_load_score) + "%\n";
        report_buffer += "--------------------------------------------------\n";
        report_buffer += "DETECTION SIGNATURE TRACKS:\n";

        if (result.detected_patterns.empty()) {
            report_buffer += " -> NO EXPLICIT LINGUISTIC TRAPS IDENTIFIED.\n";
        } else {
            for (const auto& track : result.detected_patterns) {
                report_buffer += " -> " + track + "\n";
            }
        }
        report_buffer += "--------------------------------------------------\n";

        return report_buffer.c_str();
    }

}

// Local terminal execution fallback entry point
int main() {
    std::cout << "[SYSTEM ONLINE] Enter text data package for immediate analysis:\n> ";
    std::string user_input;
    if (std::getline(std::cin, user_input)) {
        std::cout << analyze_payload(user_input.c_str()) << std::endl;
    }
    return 0;
}

