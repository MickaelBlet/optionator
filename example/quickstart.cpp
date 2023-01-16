#include <iostream>

#include "mblet/argparsor.h"

enum eLogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void argToLogLevel(eLogLevel& logLevel, bool /*isExist*/, const std::string& argument) {
    static const std::pair<std::string, eLogLevel> pairLogLevels[] = {
        std::pair<std::string, eLogLevel>("DEBUG", DEBUG), std::pair<std::string, eLogLevel>("INFO", INFO),
        std::pair<std::string, eLogLevel>("WARNING", WARNING), std::pair<std::string, eLogLevel>("ERROR", ERROR)};
    static const std::map<std::string, eLogLevel> logLevels(
        pairLogLevels, pairLogLevels + sizeof(pairLogLevels) / sizeof(*pairLogLevels));

    logLevel = logLevels.at(argument);
}

int main(int argc, char* argv[]) {
    eLogLevel logLevel = INFO;

    mblet::Argparsor args;
    args.addArgument("ARGUMENT").help("help of argument").required(true);
    args.addArgument("-v")
        .flag("--version")
        .help("help of version option")
        .action(args.VERSION)
        .defaults("Version: 0.0.0");
    args.addArgument("--option").help("help of option");
    args.addArgument("--log-level")
        .help("help of log-level")
        .metavar("LEVEL")
        .valid(new mblet::Argparsor::ValidChoise(args.vector("DEBUG", "INFO", "WARNING", "ERROR")))
        .defaults("INFO")
        .dest(logLevel, argToLogLevel);
    try {
        args.parseArguments(argc, argv, true);
        std::cout << "ARGUMENT: " << args["ARGUMENT"] << '\n';
        if (args["--option"]) {
            std::cout << "--option: " << args["--option"] << '\n';
        }
        std::cout << "--log-level: ";
        switch (logLevel) {
            case DEBUG:
                std::cout << "DEBUG";
                break;
            case INFO:
                std::cout << "INFO";
                break;
            case WARNING:
                std::cout << "WARNING";
                break;
            case ERROR:
                std::cout << "ERROR";
                break;
        }
        std::cout << std::endl;
    }
    catch (const mblet::Argparsor::ParseArgumentException& e) {
        std::cerr << args.getBinaryName() << ": " << e.what();
        std::cerr << " -- '" << e.argument() << "'" << std::endl;
        return 1; // END
    }
    return 0;
}