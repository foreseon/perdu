const char PS_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html lang = "en">
  <head>
    <title>PS_EXEC</title>
    <meta charset = "UTF-8" />
  </head>
  <body>
    <h1></h1>
    <form action="/exec">
      <fieldset>
        <legend>Configuration</legend>
        <p>
          <label></label>
        		

		<p>Execute Privilege:</p>
		<input type="radio" name="user" value="ADMIN"> Admin
		<input type="radio" name="user" value="NORMAL"> Current User
		<p></p>

		<p>Logon password of computer (leave empty if computer is not locked):</p>
		Logon Password: <input type="text" name="PASS" value=""><br>
		<p></p>
		Execute Delay: <input type="text" name="DELAY" value="">
		<p></p>
		
		
		
      </fieldset>
	  
	  <fieldset>
        <legend>Download&Execute .ps</legend>
        <p>
          <label></label>
        

		Powershell Command: <input type="text" name="ps_link" value=""><br>		
		<p></p>
		<input type="submit" value="Execute">
		
      </fieldset>
    
	  <fieldset>
        <legend>Execute Command</legend>
        <p>
          <label></label>
        

		Powershell Command: <input type="text" name="ps_command" value=""><br>		
		<p></p>
		<input type="submit" value="Execute">
		
      </fieldset>
    </form>
	
	
  </body>
</html>

<html>
<body>

</body>
</html>)=====";

const char CMD_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html lang = "en">
  <head>
    <title>CMD_EXEC</title>
    <meta charset = "UTF-8" />
  </head>
  <body>
    <h1></h1>
    <form action="/exec">
      <fieldset>
        <legend>Configuration</legend>
        <p>
          <label></label>
         		

		<p>Execute Privilege:</p>
		<input type="radio" name="user" value="ADMIN"> Admin
		<input type="radio" name="user" value="NORMAL"> Current User
		<p></p>

		<p>Logon password of computer (leave empty if computer is not locked):</p>
		Logon Password: <input type="text" name="PASS" value=""><br>
		<p></p>
		Execute Delay: <input type="text" name="DELAY" value="">
		<p></p>
		
		
		
      </fieldset>	  
    
	  <fieldset>
        <legend>Execute Command</legend>
        <p>
          <label></label>
        

		CMD Command: <input type="text" name="cmd_command" value=""><br>		
		<p></p>
		<input type="submit" value="Execute">
		
      </fieldset>
    </form>
	
	
  </body>
</html>

<html>
<body>

</body>
</html>)=====";

const char DOWNEXEC_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html lang = "en">
  <head>
    <title>DOWNLOAD_EXECUTE</title>
    <meta charset = "UTF-8" />
  </head>
  <body>
    <h1></h1>
    <form action="/exec">
      <fieldset>
        <legend>Configuration</legend>
        <p>
          <label></label>
        	
		
		<p>Execute Privilege:</p>
		<input type="radio" name="user" value="ADMIN"> Admin
		<input type="radio" name="user" value="NORMAL"> Current User
		<p></p>

		<p>Logon password of computer (leave empty if computer is not locked):</p>
		Logon Password: <input type="text" name="PASS" value=""><br>
		<p></p>
		Execute Delay: <input type="text" name="DELAY" value="">
		<p></p>		
      </fieldset>	  
    
	  <fieldset>
        <legend>Download&Execute</legend>
        <p>
          
		Download Link: <input type="text" name="download_link" value=""><br>
		<p></p>
		Destination Path: <input type="text" name="file_path" value=""><br>
		<p></p>
		<p>Execute?</p>
		<input type="radio" name="exec" value="YES"> Yes
		<input type="radio" name="exec" value="NO"> No
		<p></p>
		<p>Download With:</p>
		<input type="radio" name="method" value="Bitsadmin"> Bitsadmin
		<input type="radio" name="method" value="Powershell"> Powershell
		<input type="radio" name="method" value="VBScript"> VBScript
		<input type="radio" name="method" value="Notepad"> Notepad
		<p></p>
		
		<input type="submit" value="Execute">
		
		<p></p>		
      </fieldset>
    </form>
	
	
  </body>
</html>

<html>
<body>

</body>
</html>)=====";

