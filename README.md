# EbayBiddingIntensifier
Use an MP3 to count down to a point in time

# Why?
For years I have put the song "In the house, in a Heartbeat" from 28 Days Later on whilst waiting for my eBay auction to end. Now I can leave this running in the terminal and have it so that the song ends exactly at the auction end.
Originally, I had planned to use this to demonstrate a usage of libcurl to get information from a RESTful API, though afaik, eBay doesn't prove an API Call for a list of items a user is bidding on.
The closest I could come to this would be to make an API call to get the end time for an item ID, but if I'm having to do this each time, I may as well just have it count down to a datetime, making it more flexible.

# Building
Builds for this have only been tested in (and will most likely only work for) linux.
The repository is simply the working directory of a Netbeans (C++ Extension) project. I have been building this from netbeans directly.
Requires libmpg and ao.

