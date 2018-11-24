(function(root){
    "use strict";
    var doc = document;

    var jsonObj;

    var loadJSON = function(path, callback) {
        var xobj = new XMLHttpRequest();
        xobj.open('GET', path);
        xobj.onreadystatechange = function() {
            if (xobj.readyState === 4) {
                jsonObj = xobj.responseText;
                callback();
            }
        };
        xobj.send(null);
          
    };

    

    window.addEventListener('DOMContentLoaded', function(){

        function reqListener () {

            loadJSON("data/measurement.txt", function (){
                 creatEle(jsonObj);
                console.log(jsonObj);
    
            });

          
        }

        function creatEle (temp) {

            var dat = new Date();
            var months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
            var getMon = months[dat.getMonth()];
            var currentHours = dat.getHours();
                currentHours = ("0" + currentHours).slice(-2);
            var currentminut = dat.getMinutes();
                currentminut = ("0" + currentminut).slice(-2);
            var currentsec = dat.getSeconds();
                currentsec = ("0" + currentsec).slice(-2);

            var space = "\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0";
            var creatElem = doc.createElement("div");
                creatElem.classList.add("measurement")
            var node = doc.createTextNode("Temp: " + temp + "\xB0" + "C"  + space + "Time: " + dat.getDate() + " " + getMon + " " + dat.getFullYear() + " " + currentHours + ":" + currentminut + ":" + currentsec);
                creatElem.appendChild(node);
            var elem = doc.getElementById("temp__box");
            elem.appendChild(creatElem);    
        }

        setInterval(reqListener, 2000);

    },false);

})(this)