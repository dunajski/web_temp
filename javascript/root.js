(function(root){
    "use strict";
    var doc = document;

    window.addEventListener('DOMContentLoaded', function(){
        var temp = 24;

        var creatElem = doc.createElement("div");
            creatElem.classList.add("measurement")
        var node = doc.createTextNode("Temp: " + temp + "&deg;" +"C");
            creatElem.appendChild(node);
        
        var elem = doc.getElementById("temp__box");
            elem.appendChild(creatElem)    

        console.log("hello world!")
    },false);

})(this)