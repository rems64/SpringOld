#pragma once

#include <functional>
#include <vector>
#include <map>
#include <forward_list>
#include <string>
#include <chrono>
#include <ofbx.h>
#include <iostream>
#include <memory>
#include <fstream>
#include <sstream>
#include <initializer_list>
#include <filesystem>
#include <algorithm>
#include <thread>

#include <SpringEngine/core.hpp>
#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Misc/Macros.hpp>
#include <SpringEngine/Misc/Instrumentator.hpp>


#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>

#include <nlohmann/json.hpp>