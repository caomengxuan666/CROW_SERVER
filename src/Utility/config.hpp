/**
 * @FilePath     : /crow_server/src/Utility/config.hpp
 * @Description  : Configuration manager using INI format
 * @Author       : caomengxuan666 2507560089@qq.com
 * @Version      : 0.0.1
 * @LastEditors  : caomengxuan666 2507560089@qq.com
 * @LastEditTime : 2025-09-03 20:34:43
 * @Copyright    : PESONAL DEVELOPER CMX., Copyright (c) 2025.
**/

#pragma once

#include "../../third_party/inicpp.hpp"
#include "executable_path.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

namespace crow_server {
    namespace config {

        // Configuration file path constant
        const std::string CONFIG_FILE = getExecutableDirectory() + "/crow_server.ini";
        
        // Forward declarations
        struct OutputConfig;
        struct DeviceConfig;
        struct StreamConfig;
        struct GlobalConfig;

        // 全局配置指针
        extern std::unique_ptr<GlobalConfig> g_config;

        /**
         * Output configuration structure
         * Contains paths for CSV and image output
         */
        struct OutputConfig {
            std::string csv_path;     // Path for CSV output files
            std::string image_path;   // Path for image output files

            /**
             * Loads output configuration from INI file
             * @param ini Reference to IniManager instance
             * @return Populated OutputConfig structure
             */
            static OutputConfig load(inicpp::IniManager &ini) {
                try {
                    // Get output section
                    auto output_section = ini["output"];

                    OutputConfig config;

                    // String values
                    config.csv_path = output_section["csv_path"].String().empty() ? 
                                      "./csv/" : output_section["csv_path"].String();
                    config.image_path = output_section["image_path"].String().empty() ? 
                                        "./images/" : output_section["image_path"].String();

                    return config;
                } catch (const std::exception &e) {
                    std::cerr << "Failed to load output config: " << e.what() << std::endl;
                    throw;
                }
            }
        };
        
        /**
         * Device configuration structure
         * Contains device-related settings
         */
        struct DeviceConfig {
            std::string ip;           // Device IP address
            
            /**
             * Loads device configuration from INI file
             * @param ini Reference to IniManager instance
             * @return Populated DeviceConfig structure
             */
            static DeviceConfig load(inicpp::IniManager &ini) {
                try {
                    DeviceConfig config;
                    
                    // Get device section
                    auto device_section = ini["device"];
                    
                    // String values
                    config.ip = device_section["ip"].String().empty() ? 
                                "192.168.1.168" : device_section["ip"].String();
                    
                    return config;
                } catch (const std::exception &e) {
                    std::cerr << "Failed to load device config: " << e.what() << std::endl;
                    throw;
                }
            }
        };
        
        /**
         * Stream configuration structure
         * Contains streaming-related settings
         */
        struct StreamConfig {
            std::string rtmp_port;    // RTMP streaming port
            
            /**
             * Loads stream configuration from INI file
             * @param ini Reference to IniManager instance
             * @return Populated StreamConfig structure
             */
            static StreamConfig load(inicpp::IniManager &ini) {
                try {
                    StreamConfig config;
                    
                    // Get stream section
                    auto stream_section = ini["stream"];
                    
                    // String values
                    config.rtmp_port = stream_section["rtmp_port"].String().empty() ? 
                                       "8554" : stream_section["rtmp_port"].String();
                    
                    return config;
                } catch (const std::exception &e) {
                    std::cerr << "Failed to load stream config: " << e.what() << std::endl;
                    throw;
                }
            }
        };

        /**
         * Global application configuration structure
         * Contains top-level configuration and nested output settings
         */
        struct GlobalConfig {
            std::string title;        // Configuration file title/description
            OutputConfig output;      // Nested output configuration
            DeviceConfig device;      // Nested device configuration
            StreamConfig stream;      // Nested stream configuration

            /**
             * Loads complete configuration from INI file
             * @return Populated GlobalConfig structure
             */
            static GlobalConfig load() {
                try {
                    inicpp::IniManager ini(CONFIG_FILE);
                    std::cout << "Loaded configuration file: " << CONFIG_FILE << std::endl;

                    GlobalConfig config;
                    config.title = ini[""]["title"].String().empty() ? 
                                   "Crow Server Configuration" : ini[""]["title"].String();
                    config.output = OutputConfig::load(ini);
                    config.device = DeviceConfig::load(ini);
                    config.stream = StreamConfig::load(ini);

                    return config;
                } catch (const std::exception &e) {
                    std::cerr << "Failed to load global config: " << e.what() << std::endl;
                    throw;
                }
            }
        };

        /**
         * Initializes default configuration file if it doesn't exist or is empty
         * Creates standard sections and default values for first-time setup
         */
        inline void initialize_default_config() {
            try {
                // Check if file exists and has content using filesystem
                bool file_valid = false;
                if (std::filesystem::exists(CONFIG_FILE)) {
                    if (std::filesystem::file_size(CONFIG_FILE) > 0) {
                        file_valid = true;

                    } else {
                        std::cout << "Configuration file is empty - recreating: " << CONFIG_FILE << std::endl;
                    }
                }

                if (file_valid) {
                    return;
                }

                // Create new configuration file with defaults
                inicpp::IniManager ini(CONFIG_FILE);
                std::cout << "Creating default configuration file: " << CONFIG_FILE << std::endl;
                
                // Output section configuration
                ini.set("output", "csv_path", "./csv/");
                ini.set("output", "image_path", "./images/");

                // Add comments for output section
                ini.setComment("output", "csv_path", "Path for CSV output files");
                ini.setComment("output", "image_path", "Path for image output files");
                
                // Device section configuration
                ini.set("device", "ip", "192.168.1.168");
                ini.setComment("device", "ip", "Device IP address");
                
                // Stream section configuration
                ini.set("stream", "rtmp_port", "8554");
                ini.setComment("stream", "rtmp_port", "RTMP streaming port");

                // Root section configuration
                ini.set("title", "Crow Server Configuration");
                ini.setComment("title", "Auto-generated configuration file for Crow Server");

                // Force configuration write
                ini.parse();
                std::cout << "Successfully created default configuration" << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "Configuration initialization failed: " << e.what() << std::endl;
                throw;
            }
        }

        /**
         * Prints configuration values
         * @param config Reference to GlobalConfig instance to display
         */
        inline void print_config(const GlobalConfig &config) {
            std::cout << "===== Crow Server Configuration =====" << std::endl;
            std::cout << "Title: " << config.title << std::endl;
            std::cout << "CSV Path: " << config.output.csv_path << std::endl;
            std::cout << "Image Path: " << config.output.image_path << std::endl;
            std::cout << "Device IP: " << config.device.ip << std::endl;
            std::cout << "RTMP Port: " << config.stream.rtmp_port << std::endl;
            std::cout << "=====================================" << std::endl;
        }

        /**
         * Lists all configuration sections and key-value pairs
         * Useful for debugging and verification of configuration structure
         */
        inline void list_config_sections() {
            try {
                inicpp::IniManager ini(CONFIG_FILE);
                std::cout << "Listing all configuration sections from: " << CONFIG_FILE << std::endl;

                for (const auto &section: ini.sectionsList()) {
                    std::cout << "\n[" << section << "]" << std::endl;
                    for (const auto &[key, value]: ini.sectionMap(section)) {
                        std::cout << "  " << key << " = " << value << std::endl;
                    }
                }
            } catch (const std::exception &e) {
                std::cerr << "Failed to list configuration sections: " << e.what() << std::endl;
                throw;
            }
        }

    } // namespace config
} // namespace crow_server