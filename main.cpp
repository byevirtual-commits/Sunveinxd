#include <dpp/dpp.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include <string>
#include <vector>
#include <sstream>

int main() {
    const char* env_token = std::getenv("TOKEN");
    const char* env_channels = std::getenv("CHANNEL_IDS");
    const char* env_message = std::getenv("MESSAGE");

    if (!env_token || !env_channels || !env_message) {
        std::cerr << "HATA: Eksik ortam degiskenleri! Lutfen Render uzerinden TOKEN, CHANNEL_IDS ve MESSAGE ekleyin.\n";
        return 1;
    }

    std::string token = env_token;
    std::string message = env_message;
    std::string channels_str = env_channels;

    std::vector<dpp::snowflake> channel_ids;
    std::stringstream ss(channels_str);
    std::string item;
    
    while (std::getline(ss, item, ',')) {
        try {
            channel_ids.push_back(std::stoull(item));
        } catch (...) {
            std::cerr << "Gecersiz kanal ID formati atlandi: " << item << "\n";
        }
    }

    if (channel_ids.empty()) {
        std::cerr << "HATA: Gecerli hic kanal ID'si bulunamadi.\n";
        return 1;
    }

    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_ready([&bot, channel_ids, message](<const dpp::ready_t& event>) {
        std::cout << "Bot basariyla baglandi: " << bot.me.username << std::endl;

        std::thread([&bot, channel_ids, message]() {
            for (size_t i = 0; i < channel_ids.size(); ++i) {
                dpp::message msg(channel_ids[i], message);
                bot.message_create(msg);
                
                std::cout << channel_ids[i] << " ID'li kanala mesaj gonderildi.\n";

                if (i < channel_ids.size() - 1) {
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            }
            std::cout << "Belirtilen tum kanallara mesaj atildi!\n";
        }).detach();
    });

    bot.start(dpp::st_wait);
    return 0;
}
