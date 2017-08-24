#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2
 
const char* ssid     = "ssid name";
const char* password = "password";
 
ESP8266WebServer server(80);

// This is for the ESP8266 processor on ESP-01 
DHT dht(DHTPIN, DHTTYPE, 15); // 11 works fine for ESP8266
float tarr[5];
float harr[5];
float humidity, temp_f;  // Values read from sensor
String webString="";     // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor
 
void handle_root() {
  server.send(200, "text/plain", "Hello from the weather esp8266, read from /temp or /humidity");
  delay(100);
}
 
void setup(void)
{
  // You can open the Arduino IDE Serial Monitor window to see what the code is doing
  Serial.begin(115200);  // Serial connection from ESP-01 via 3.3v console cable
  dht.begin();           // initialize temperature sensor
 
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", handle_root);
  
  server.on("/temp", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    gettemperature();       // read sensor
    webString=
    String("<!Doctype HTML><html>") + "<head>" + "<meta name=\"viewport\" content=\"width=device-width\" />"+ "<link href=\"~/Content/bootstrap.css\" rel=\"stylesheet\" />"+
      "<script src=\"https://code.highcharts.com/highcharts.js\"></script>"+
      "<script src=\"https://code.highcharts.com/modules/exporting.js\"></script>"+
      "<style>"+
      ".divider {"+
      "background: #999;"+
      "height: 0;"+
      "margin-top: 15px;"+
      "margin-bottom: 15px;"+
      "background: transparent;"+
      "padding: 50px;"+
      "}"+
      ".main-content {"+
      " /* background: #fff; */"+
      "background:linear-gradient(to right, #1a2980, #26d0ce); /* W3C, IE 10+/ Edge, Firefox 16+, Chrome 26+, Opera 12+, Safari 7+ */"+
      "//max-width: 1080px;"+
      "margin-left: auto;"+
      "margin-right: auto;"+
      "padding-top: 50px;"+
      "padding-bottom: 50px;"+
      "box-shadow: 0 0 5px 5px rgba(0, 0, 0, 0.3);"+
      /*overflow: auto;*/
      "}"+
      ".align{"+
      "text-align:center;"+
      "align-items:center;"+
      "color: wheat;"+
      "}"+
      " .form_field {"+
      "border: 1px solid #999;"+
      "padding: 10px 20px;"+
      "width: inherit;"+
      "border-radius: 4px;"+
      " }"+
      "#container {"+
      "background: transparent;"+
      "min-width: 310px;"+
      "max-width: 800px;"+
      "height: 400px;"+
      "margin: 0 auto"+
      "}"+          
      "</style>"+
      "<title>WebDashboard</title>"+
      "</head>"+
      "<body>"+
      "<div class=\"main-content\">"+
      "<header>"+
      "<div class=\"align\">"+
      "<h1>WebDashboard POC</h1>"+
      "</div>"+
      "</header>"+
      "<div class=\"align\">"+
      "Live Temperature:" + String(temp_f) +"C"+
      "<div class=\"divider\" id=\"slider\">"+
      "<!--<div class=\"align\">"+
      "<label class=\"label1\">Select the SensorID</label>"+
      "<select id=\"SensorId\" class=\"form_field\">"+
      "<option value=\"1\">1. Temperature Sensor</option>"+
      "<option value=\"2\">2. Humidity Sensor</option>"+
      "</select><label class=\"label1\">Enter the value</label><input id=\"SensorData\"  class=\"form_field\" type=\"text\" name=\"SD\" /><input id=\"btnSave\" type=\"submit\" label=\"post\"/>"+
      "</div>-->"+ 
      "</div>"+
      "<div id=\"SensorDashBoard\" class=\"align\">"+
      "</div>"+             
      "<br>"+
      "<div class=\"jumbotron bgcolo\" align=center>"
      "<div id=\"container\"></div>"+
      "<script>"+
      "var d = new Date();"+
      "var n = d.getSeconds();"+
      "Highcharts.chart('container', {"+
      "title: {"+
      "text: 'SENSOR DATA'"+
       "},"+
      "subtitle: {"+
      "text: 'Source: esp8266 TEMPERATURE SENSOR KIT'"+
      "},"+
      "yAxis: {"+
      "title: {"+
      "text: 'Temperature'"+
      "}"+
      "},"+
      "legend: {"+
      "layout: 'vertical',"+
      "align: 'right',"+
      "verticalAlign: 'middle'"+
      "},"+
      "plotOptions: {"+
      "series: {"+
      "pointStart:n"+
      " }"+
      "},"+
      "series: [{"+
      "name: 'Temp Value',"+
      "data: ["+tarr[0]+","+tarr[1]+","+tarr[2]+","+tarr[3]+","+tarr[4]+"]"+
      "}]"+
      "});"+
      "</script>"+ 
      "</div>"+
      "<div class=\"navbar navbar-inverse bg-inverse\" align=\"center\"><h6>Designed by Bhagirath Tallapragada G varchala</h6></div>"+
      "</div>"+
      "</body>"+
      "</html>"+ "%";//"Humidity: "+String((int)humidity)+"%";
    server.send(200, "text/html", webString);//"Temperature: "+String((int)temp_f)+" F";   // Arduino has a hard time with float to string
    //server.send(200, "text/plain", webString);            // send to someones browser when asked
  });
 
  server.on("/humidity", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    gettemperature();           // read sensor
    webString=
      String("<!Doctype HTML><html>") + "<head>" + "<meta name=\"viewport\" content=\"width=device-width\" />"+ "<link href=\"~/Content/bootstrap.css\" rel=\"stylesheet\" />"+
      "<script src=\"https://code.highcharts.com/highcharts.js\"></script>"+
      "<script src=\"https://code.highcharts.com/modules/exporting.js\"></script>"+
      "<style>"+
      ".divider {"+
      "background: #999;"+
      "height: 0;"+
      "margin-top: 15px;"+
      "margin-bottom: 15px;"+
      "background: transparent;"+
      "padding: 50px;"+
      "}"+
      ".main-content {"+
      " /* background: #fff; */"+
      "background:linear-gradient(to right, #1a2980, #26d0ce); /* W3C, IE 10+/ Edge, Firefox 16+, Chrome 26+, Opera 12+, Safari 7+ */"+
      "//max-width: 1080px;"+
      "margin-left: auto;"+
      "margin-right: auto;"+
      "padding-top: 50px;"+
      "padding-bottom: 50px;"+
      "box-shadow: 0 0 5px 5px rgba(0, 0, 0, 0.3);"+
      /*overflow: auto;*/
      "}"+
      ".align{"+
      "text-align:center;"+
      "align-items:center;"+
      "color: wheat;"+
      "}"+
      " .form_field {"+
      "border: 1px solid #999;"+
      "padding: 10px 20px;"+
      "width: inherit;"+
      "border-radius: 4px;"+
      " }"+
      "#container {"+
      "background: transparent;"+
      "min-width: 310px;"+
      "max-width: 800px;"+
      "height: 400px;"+
      "margin: 0 auto"+
      "}"+          
      "</style>"+
      "<title>WebDashboard</title>"+
      "</head>"+
      "<body>"+
      "<div class=\"main-content\">"+
      "<header>"+
      "<div class=\"align\">"+
      "<h1>WebDashboard POC</h1>"+
      "</div>"+
      "</header>"+
      "<div class=\"align\">"+
      "Live Humidity:" + String(humidity) +"Percent"+
      "<div class=\"divider\" id=\"slider\">"+
      "<!--<div class=\"align\">"+
      "<label class=\"label1\">Select the SensorID</label>"+
      "<select id=\"SensorId\" class=\"form_field\">"+
      "<option value=\"1\">1. Temperature Sensor</option>"+
      "<option value=\"2\">2. Humidity Sensor</option>"+
      "</select><label class=\"label1\">Enter the value</label><input id=\"SensorData\"  class=\"form_field\" type=\"text\" name=\"SD\" /><input id=\"btnSave\" type=\"submit\" label=\"post\"/>"+
      "</div>-->"+ 
      "</div>"+
      "<div id=\"SensorDashBoard\" class=\"align\">"+
      "</div>"+             
      "<br>"+
      "<div class=\"jumbotron bgcolo\" align=center>"
      "<div id=\"container\"></div>"+
      "<script>"+
      "var d = new Date();"+
      "var n = d.getSeconds();"+
      "Highcharts.chart('container', {"+
      "title: {"+
      "text: 'SENSOR DATA'"+
       "},"+
      "subtitle: {"+
      "text: 'Source: esp8266 HUMIDITY SENSOR KIT'"+
      "},"+
      "yAxis: {"+
      "title: {"+
      "text: 'Humidity'"+
      "}"+
      "},"+
      "legend: {"+
      "layout: 'vertical',"+
      "align: 'right',"+
      "verticalAlign: 'middle'"+
      "},"+
      "plotOptions: {"+
      "series: {"+
      "pointStart:n"+
      " }"+
      "},"+
      "series: [{"+
      "name: 'Humidity value',"+
      "data:["+harr[0]+","+harr[1]+","+harr[2]+","+harr[3]+","+harr[4]+"]"+
      "}]"+
      "});"+
      "</script>"+ 
      "</div>"+
      "<div class=\"navbar navbar-inverse bg-inverse\" align=\"center\"><h6>Designed by Bhagirath Tallapragada and G Varchala</h6></div>"+
      "</div>"+
      "</body>"+
      "</html>"+ "%";//"Humidity: "+String((int)humidity)+"%";
    server.send(200, "text/html", webString);               // send to someones browser when asked
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
} 
 
void gettemperature() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();
  static int i=0;
  if(currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor 
    previousMillis = currentMillis;   
 
    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature();
    tarr[i]=temp_f;
    harr[i]=humidity;
    i++;
    if(i==5){
      for(int j=0;j<4;j++){
        int a[5];
      a[j]=a[j+1];
      }
      i=4;
    }
    }
    // Read temperature as Fahrenheit
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp_f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }

