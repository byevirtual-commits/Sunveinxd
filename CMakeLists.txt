cmake_minimum_required(VERSION 3.14)
project(discord_bot)

set(CMAKE_CXX_STANDARD 17)

# D++ Kütüphanesini otomatik indir ve kur
include(FetchContent)
FetchContent_Declare(
  dpp
  GIT_REPOSITORY https://github.com/brainboxdotcc/DPP.git
  GIT_TAG        v10.0.35
)
FetchContent_MakeAvailable(dpp)

add_executable(bot main.cpp)

# Hatanın düzeltildiği yer: dpp::dpp yerine sadece dpp kullanıyoruz
target_link_libraries(bot dpp)
