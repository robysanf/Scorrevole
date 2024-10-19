
function inizia() {
  send("iniz");
  
}

function calcola_encoder() {
  send("enco");
 
}

function imposta_pos_zero() {
  send("pos0");
 
}

function imposta_pos_aperto() {
	
  send("posA");
 
}

function calcola_imp() {
	raggio=document.getElementById("fraggio").value;
	if(validateNum(raggio))
	{
      send("impu"+raggio);
      
	}
}

function move() {
  send("move");
 
}

function chiude() {
  send("moto-");
  
}

function apre() {
  send("moto");
  
}

function cons() {
	document.getElementById("fraggio").value;
  send("cons");
  
}

function velo() {
  send("velo");
 
}

function save(a) {
	if(a==1)
	   document.getElementById("CONFIGURAZIONE").value='1';
	send(makeResponseToSave());
     
}


function apri() {
  send("apri");
 
}

function chiudi() {
  send("chiu");
 
}

function stop() {
  send("stop");
 
}

function vars() {
  send("VARS");
 
}

function test() {
  send("TEST");
 
}

function set() {
	makeConfigHtml(last_response);
 	document.getElementById("gridContainer").style.visibility='visible';
 
}
function set_reset() {
  send("setr");
  
}


function validateNum(x) {
  let text;
  if (isNaN(x) || x < 1 || x > 10000) {
    text = "Input not valid";
	document.getElementById("message").innerHTML = text;
    return false;
  } else {
	  document.getElementById("message").innerHTML = "";
    return true;
  }
  
}
function removeAllChildNodes(parent) {
    while (parent.firstChild) {
        parent.removeChild(parent.firstChild);
    }
}
	