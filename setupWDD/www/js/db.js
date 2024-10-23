function init_db(){
//*************************  DATABASE   ********************************** 
mongogx = new OGX.Mongogx();

}
function dbtest(){
	
	
	
	
	
	mongogx.createDatabase('my_project');	
	mongogx.setDatabase('my_project');	
	//console.log(mongogx.getCollections());
	mongogx.createCollection('users');		
	
mongogx.setCollection('users');		
	
	/*mongogx.insert({first_name:'roby', age:42, sex:'male', location:{state:'ON', city:'Toronto'}, favorites:{meals:[{name:'pizza'}, {name:'pasta'}]}});
		mongogx.insert({first_name:'Tania', age:38, sex:'female', location:{state:'ON', city:'Toronto'}});
		mongogx.insert({first_name:'Julien', age:45, sex:'male', location:{state:null, city:'Stockholm'}});
		mongogx.insert({first_name:'George', age:55, sex:'male', location:{state:'QC', city:'Montreal'}, arts:{martial:['kickboxing', 'wresting']}});
		
		{project:'LA CAPILLA', floor_num:42, sex:'male', location:[{floor:1, name:'Cucina',ip:'192.168.81.100'},{floor:2, name:'Sala',ip:'192.168.81.50'}]}
		
		
		
		
	*/
	pi="George"
	console.log(mongogx.find({'first_name':{'$in':pi}}));
	a=mongogx.find({'arts.martial':{'$in':'kickboxing'}});
	//user=a[0].first_name;
	//delete_db();
	mongogx.deleteMany({'first_name':{'$in':pi}});
}

function find_db(username,pwd){
	//se non esistevano db e collection le crea
	/*mongogx = new OGX.Mongogx('my_project');
	mongogx.createDatabase('my_project');	
	mongogx.createCollection('users');
	mongogx.setDatabase('my_project');
    mongogx.setCollection('users');*/
    a=mongogx.find({'first_name':{'$all':''}});
	if(a.length==0){// verifico se è vuoto in tal caso devo fare registrare il primo utente	
		document.getElementById("login").style.visibility='hidden';
		document.getElementById("central").style.visibility='hidden';
		document.getElementById("register").style.visibility='visible';
		user="unregistred";
		return false;
	}
	
    us=mongogx.find({'first_name':{'$in':username}})
	if(us.length==1)
	{
		if( pwd==us[0].age){
			user=us.first_name;
			return true;
		}
		}else{
		
		//propongo registrazione
	}
	return false;
}

function insert_db(key){
	//se non esistevano db e collection le crea
	
    a=mongogx.find({'first_name':{'$in':key}});
	if(a.length!=0){// verifico se non è vuoto in tal caso l'utente esiste già	
		
		return 2;
	}
	m=document.getElementById("email").value;
	u=document.getElementById("username").value;
	p=document.getElementById("psw").value;
	p_r=document.getElementById("psw-repeat").value;
    resp=mongogx.insert({first_name:key, age:p, sex:m, location:{state:'ON', city:'Toronto'}, favorites:{meals:[{name:'pizza'}, {name:'pasta'}]}});
	if(resp)
	{
				return true;
		
	}
	return false;
}
function delete_db(){
	
/*	mongogx = new OGX.Mongogx();
	mongogx.createDatabase('my_project');
	mongogx.setDatabase('my_project');
	mongogx.createCollection('users');		
	
mongogx.setCollection('users');	*/
	mongogx.deleteCollection('users');
	
	
}