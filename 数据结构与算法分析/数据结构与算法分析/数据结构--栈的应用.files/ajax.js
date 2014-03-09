<!--
var http_request = false;
var upnum;

function CreateXMLHttp()
{
	http_request = false;
	if (window.XMLHttpRequest) { // Mozilla, Safari,...
		http_request = new XMLHttpRequest();
	} else if (window.ActiveXObject) { // IE
		try {
			http_request = new ActiveXObject("Msxml2.XMLHTTP");
		} catch (e) {
			try {
				http_request = new ActiveXObject("Microsoft.XMLHTTP");
			} catch (e) {}
		}
	}
	if (!http_request) {
		alert('Giving up :( Cannot create an XMLHTTP instance');
		return false;
	}
}
function Up(id) {
	CreateXMLHttp();
	var url = "bbsaction.asp?action=up&id=" + id;
	upnum = document.getElementById("upnum").innerHTML;
	http_request.onreadystatechange = alertContents;
	http_request.open('GET', url, true);
	http_request.send(null);
}

function alertContents() {
	document.getElementById("upnum").innerHTML = "<img src='image/loading.gif' />";
	if (http_request.readyState == 4) {
		if (http_request.status == 200) {
				switch(parseInt(http_request.responseText)){
					case 0:
						document.getElementById("upnum").innerHTML = upnum;
						alert("您已推荐过此帖");
						break;
					case -1:
						document.getElementById("upnum").innerHTML = upnum;
						alert("您尚未登陆");
						break;
					default:
						document.getElementById("upnum").innerHTML = http_request.responseText;
						document.getElementById("uptext").innerHTML = "已推荐";
						break;
				}
		}
		else
			alert('There was a problem with the request.');
	}
}
//-->