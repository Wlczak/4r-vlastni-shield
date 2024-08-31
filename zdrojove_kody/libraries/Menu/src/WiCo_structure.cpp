#include "WiCo.h"

void WiCo::setWebStructure()
{
	if (!isWebserverRunning)
		return;
	server->on("/",[this]() 
	{
	String output = "";
	output += "<!DOCTYPE html>";
	output += "<html lang=\"en\">";
	output += "    <head>";
	output += "        <meta charset=\"UTF-8\" />";
	output += "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />";
	output += "        <link rel=\"stylesheet\" href=\"style.css\" />";
	output += "        <title>test</title>";
	output += "    </head>";
	output += "    <body>";
	output += "        <h1>hi there</h1>";
	output += "        <img src=\"logo.svg\" alt=\"\">";
	output += "        <form action=\"/test\" method=\"post\">";
	output += "            <input type=\"text\" name=\"idk_name\" id=\"\" placeholder=\"text here\">";
	output += "            <button type=\"submit\">submit</button>";
	output += "        </form>";
	output += "    </body>";
	output += "</html>";

	server->send(200, "text/html", output);
	});

	server->on("/not in use",[this]() 
	{
	String output = "";

	server->send(200, "text/html", output);
	});

	server->on("/style.css",[this]() 
	{
	String output = "";
	output += "h1{";
	output += "    border: 1px solid black;";
	output += "    background-color: pink;";
	output += "}";

	server->send(200, "text/css", output);
	});

	server->on("/test",[this]() 
	{
	auto idk_name= server->arg("idk_name");
	

	String output = "";
	
	JsonDocument json;
	json["test"] = idk_name;
	output = serializeJson(json, Serial);

	server->send(200, "text/plain", output);
	});

}