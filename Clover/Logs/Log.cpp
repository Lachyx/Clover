#include <clover.h>

void Log(const std::string& message, LogLevel level) {
	if (Config::Logs) {
        FILE* logFile;
        fopen_s(&logFile, "log.txt", "a");

        const char* levelStr = (level == INFO) ? "[INFO] " :
            (level == WARN) ? "[WARN] " : "[CRITICAL] ";

        if (logFile) {
            fprintf(logFile, "%s%s\n", levelStr, message.c_str());
            fclose(logFile);
        }
   }
}