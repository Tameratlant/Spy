**This project was created for simple visual analysis of various statistics of your correspondence in Telegram. Spy allows you to view aspects such as the average response time, message statistics by month, day, and hour. Spy also provides keyword search.** 

**How it work**

In Tg correspondence is stored in json format. For parsing, this project used https://github.com/nlohmann/json.

Due to the fact that this library is not designed for large json files, it is necessary to split the original correspondence into smaller fragments (file separate.cpp).

Date.hpp implemented date classes for convenient date storage and processing.

Dialogue.hpp contains discriptions of the message and dialogue classes, as well as methods for working with the chat as a whole. For example, to search, add new fragments of the chat.

**How to build**

To build, input the path to file with the correspondence in file init.txt and run the Makefile.
