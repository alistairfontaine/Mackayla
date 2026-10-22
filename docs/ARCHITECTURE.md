# ARCHITECTURE PROFILE // MACKAYLA

## 1. DATA INGESTION PIPELINE
Inputs are captured through a pure C++ string buffer, avoiding standard heap overhead where possible. The text is parsed incrementally using character-by-character validation checks.

## 2. METRIC WEIGHT MATRICES
* **Evasion (EV_VEC):** Tracks linguistic deflections (e.g., "listen", "to be honest", "honestly", "reframe").
* **Fallacy (FL_VEC):** Maps rhetorical traps (e.g., "always", "never", "everyone", "attack").
* **Emotional Load (EM_VEC):** Evaluates psychological leverage points.

## 3. WASM BINDING LAYER
The C++ state results are packed into a flat struct and pushed across the WebAssembly boundary to the static HTML/JS runtime loop without external serialization frameworks.

