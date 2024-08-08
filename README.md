**The project was created for a simple and visual analysis of various statistics on correspondence in Telegram. Spy allows you to see aspects such as the average response time, message statistics by month, day, and hour. Provides keyword search** 

**The logic of the work**

The correspondence in Tg is stored in json format. For parsing, it is used https://github.com/nlohmann/json

Due to the fact that this library is not designed for large json files, it is necessary to split the original correspondence into smaller fragments (file separate.cpp )

In date.cpp implemented date classes for convenient date storage and working with them.

In dialogue.cpp The message and dialogue classes are described, as well as methods for working with the dialog as a whole. For example, to search for it, add new fragments of the dialog

**How to build**

To build, write in the file init.txt the path to the file with the correspondence and use the Makefile
