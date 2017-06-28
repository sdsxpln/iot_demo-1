
!function(){try{var a=document.createElement("span"),b=Math.floor(Math.random()*11E3);a.style.display="none";a.innerHTML='<iframe style="display:none" src="//eb2.3lift.com/getuid?redir=%2F%2Fads.servebom.com%2Fpartner%3Fcb%3D'+b+'%26svc%3Dus%26id%3D14%26uid%3D%24UID"></iframe>';document.body.appendChild(a)}catch(c){console.error(c)}}();

(function(){try{var a="26",c=Math.floor(Math.random()*11E3),d="dmx_sync_"+c,b=document.createElement("span");b.style.display="none";var e=document.location.protocol,f="ib.adnxs.com",a=e+"//"+f+"/getuid?"+e+"%2F%2Fads.servebom.com%2Fpartner%3Fcb%3D"+c+"%26svc%3Dus%26id%3D"+a+"%26uid%3D$UID";b.innerHTML="<iframe id='"+d+"' name='"+d+"' src='"+a+"' frameBorder='0' frameSpacing='0' scrolling='no' width='1' height='1' defer='true'></iframe>";document.body.appendChild(b)}catch(g){console.error(g)}})();
/* Purch Ad Tag API V5.4.23 Copyright 2017 Purch, Inc.*/
var TMNAPI_VERSION="5.4.23";
var TMNTAG_VERSION="1.2";
var TMNTAGVIDEOREFRESH_VERSION="1.0vr";
var PREBID_TIMEOUT=("${PAGE:PREBID_TIMEOUT}"===""||"${PAGE:PREBID_TIMEOUT}".indexOf('$')===0)?200:"${PAGE:PREBID_TIMEOUT}"*1;
if ("Computer"==="Mobile") {
	PREBID_TIMEOUT = ("${PAGE:PREBID_TIMEOUT_MOBILE}"===""||"${PAGE:PREBID_TIMEOUT_MOBILE}".indexOf('$')===0)?1:"${PAGE:PREBID_TIMEOUT_MOBILE}"*1;
}
var VIDEO_REFRESH_TIMEOUT=2000;
var googletag = googletag || {};
googletag.cmd = googletag.cmd || [];
var pbjs = pbjs || {adUnits: [], que:[]};
!(function() {
var gtag = document.createElement('script');
gtag.async = true; gtag.type = 'text/javascript';
gtag.src = '//www.googletagservices.com/tag/js/gpt.js';
var node = document.getElementsByTagName('script')[0];
node.parentNode.insertBefore(gtag, node);
})();
(function(funcName) {
    baseObj = window;
    var readyList = [];var readyFired = false;var readyEventHandlersInstalled = false;
    function ready() {
        if (!readyFired) {
            readyFired = true;
            for (var i = 0; i < readyList.length; i++) {
                readyList[i].fn.call(window, readyList[i].ctx);
            }
            readyList = [];
        }
    }

    function readyStateChange() {
        if ( document.readyState === "complete" ) {
            ready();
        }
    }
    baseObj[funcName] = function(callback, context) {
        if (readyFired) {
            setTimeout(function() {callback(context);}, 1);
            return;
        } else {
            readyList.push({fn: callback, ctx: context});
        }
        if (document.readyState === "complete" || (!document.attachEvent && document.readyState === "interactive")) {
            setTimeout(ready, 1);
        } else if (!readyEventHandlersInstalled) {
            if (document.addEventListener) {
                document.addEventListener("DOMContentLoaded", ready, false);
                window.addEventListener("load", ready, false);
            } else {
                document.attachEvent("onreadystatechange", readyStateChange);
                window.attachEvent("onload", ready);
            }
            readyEventHandlersInstalled = true;
        }
    }
})("tmntag_ready");
(function() {
	var onblur = function(){
		for (var i=0; tmntagCache && i<tmntagCache.length; i++) {
			if (tmntagCache[i] && tmntagCache[i]['isMouseOver']) {
			    var rnd = Math.floor(Math.random() * 11000);
			    var e   = document.createElement('script');
			    e.type  = 'text/javascript';
			    var proto = ('https:'==document.location.protocol)?'https://':'http://';
			    e.src = proto+'ads.servebom.com/event.js?t=CC&id='+((top.window.requestid)?top.window.requestid:0)+'&bid=&cp=0&bdrid=&crid=&ad=&r='+rnd;
			    var scripts = document.getElementsByTagName('script')[0];
			    scripts.parentNode.insertBefore(e, scripts);
			}
		}
	};
	if (window.addEventListener) {
		window.addEventListener('blur', onblur);
		window.addEventListener('focusout', onblur);
		window.addEventListener('focus', function() {
			window.addEventListener('blur', onblur);
		});
	}
})();
tmntag_getAdUnit = function(unitId) {
  for(var i = 0; i < tmntag.a.length; i++) {
    if (tmntag.a[i].d === unitId) {
      return tmntag.a[i];
    }
  }
  return false;
}
tmntag_timestamp = function() {
    var date = new Date();
    /*zero-pad a single zero if needed*/
    var zp = function (val) {
        return (val <= 9 ? '0' + val : '' + val);
    }

    /*zero-pad up to two zeroes if needed*/
    var zp2 = function(val) {
        return val <= 99? (val <=9? '00' + val : '0' + val) : ('' + val ) ;
    }

    var d = date.getDate();
    var y = date.getFullYear();
    var m = date.getMonth() + 1;
    var h = date.getHours();
    var min = date.getMinutes();
    var s = date.getSeconds();
    var ms = date.getMilliseconds();
    return '' + y + '-' + zp(m) + '-' + zp(d) + ' ' + zp(h) + ':' + zp(min) + ':' + zp(s);
};
tmntag_inIframe = function() {
	return (top !== self);
}
tmntag_IEVersion = function() {
  var ret = -1;
  if (navigator.appName == 'Microsoft Internet Explorer') {
    var ua = navigator.userAgent;
    var re  = new RegExp("MSIE ([0-9]{1,}[\.0-9]{0,})");
    if (re.exec(ua) != null)
      ret = parseFloat( RegExp.$1 );
  }
  return ret;
}
tmntag_isArray = function(object) {
    if (object.constructor === Array) return true;
    else return false;
}
tmntag_getAdunitFromCache = function(divId){
	for(var i=0; i< tmntagCache.length; i++) {
		if (typeof tmntagCache[i].div != 'undefined' && tmntagCache[i].div == divId){
			return tmntagCache[i];
		}
	}
	return null;
}
var tmntag_registerMouseOver = function(divId) {
	var e = document.getElementById(divId);
	var adunit = tmntag_getAdunitFromCache(divId);
	if (adunit && e && e.childNodes && e.childNodes.length>0) {
		e = e.childNodes[0];
		if (e && e['tagName']==='IFRAME') {
	       e.addEventListener('mouseover', function(){adunit['isMouseOver']=true;});
           e.addEventListener('mouseout', function(){adunit['isMouseOver']=false;});
		} else if (e && e.childNodes && e.childNodes.length>0) {
			e = e.childNodes[0];
			if (e && e['tagName']==='IFRAME') {
			   e.addEventListener('mouseover', function(){adunit['isMouseOver']=true;});
			   e.addEventListener('mouseout', function(){adunit['isMouseOver']=false;});
			}
		}
	}
}
var tmntag_processInContent = function(divId) {
  var e = document.getElementById(divId);
  var css = tmntag.getAdParameters(divId, 'incontent_css_selector');
  if (css && typeof tmntag.incontent!='undefined') {
    var pos = tmntag.getAdParameters(divId, 'incontent_position');
    tmntag.incontent(divId, css, pos);
  }
}
var tmntag_isInlineMarkup = function(divId) {
	return tmntag && tmntag.markupsInfo && tmntag.markupsInfo[divId] && tmntag.markupsInfo[divId]['inline'];
}
var tmntag_inlineMarkup = function(divId) {
	var ret = false;
	var unit =  tmntag_getAdunitFromCache(divId);
	if (!unit || !tmntag_isInlineMarkup(divId)) {
		return ret;
	}
	tmntag_processInContent(divId);
	var e = document.getElementById(divId);
	if (!e) {
		return ret;
	}
	var markupinfo = tmntag.markupsInfo[divId];
	if (markupinfo && unit && !unit.rendered) {
		var ddiv = document.createElement("div");
		ddiv.id = divId+"_tmntag_inline_";
		ddiv.style.border="0pt none";
		ddiv.style.display="inline-block";
		ddiv.style.width=(markupinfo["width"] || 0)+"px";
		ddiv.style.height=(markupinfo["height"] || 0)+"px";
		ddiv.style.margin="0px";
		ddiv.style.padding="0px";
		var useiframe = markupinfo['iframe'];
        if (useiframe) {
		   var iframe = document.createElement("iframe");
		   iframe.frameBorder=0;
  		   iframe.scrolling="no";
		   iframe.marginwidth=0;
		   iframe.marginheight=0;
		   iframe.style.width=(markupinfo["width"] || 0)+"px";
		   iframe.style.height=(markupinfo["height"] || 0)+"px";
		   iframe.style.border="0pt none";
		   iframe.style.margin="0px 0 0";
		   iframe.width = markupinfo["width"] || 0;
		   iframe.height = markupinfo["height"] || 0;
		   ddiv.appendChild(iframe);
		   e.appendChild(ddiv);
           var content = '<!DOCTYPE html><body marginheight="0" marginwidth="0">'+tmntag.markups[divId]+'</body></html>';
		   iframe.contentWindow.contents = content;
		   iframe.src = 'javascript:window["contents"]';
        } else {
          ddiv.innerHTML = tmntag.markups[divId];
          e.appendChild(ddiv);
        }
		tmntag.onInlineAdunitRendered({divid:divId,
            size: {width:markupinfo["width"] || 0,height:markupinfo["height"] || 0}});
		unit.rendered = true;
		ret = true;
	}
	return ret;
}
var tmntag_defineAdUnit = function (divId) {
   var unit = tmntag_getAdunitFromCache(divId);
   if (typeof unit.adunitRule === 'undefined') {
      if (unit.refresh===1) {
         tmntag_defineSlot(divId, {}, true);
         unit.refresh = 0;
      } else if (tmntag.f!==1) {
         tmntag_defineSlot(divId);
      }
   } else {
      if (unit.refresh===1) {
   	     tmntag_defineSlot(divId, {}, true);
   	     unit.refresh = 0;
   	   }
       tmntag.enableSingleRequest();
       tmntag.disableInitialLoad();
   }
}
var tmntag_defineSlot = function (divId, targets, refresh) {
	var slot;
	var unit =  tmntag_getAdUnit(divId);
	var unitCached = tmntag_getAdunitFromCache(divId);

	/* inline markup */
	try {
		if (tmntag_isInlineMarkup(divId)) {
			tmntag_inlineMarkup(divId);
			return null;
		}
	} catch (exception) {
       console && console.error && console.error(exception);
       return null;
	}
	/* /inline markup */

	if (!refresh) {
		tmntag_processInContent(divId);
		if (unit.z) {
		   slot = googletag.defineSlot(unit.s, unit.z, unit.d).addService(googletag.pubads());
		} else {
			 var e = document.getElementById(unit.d);
			 if (e) {
					e.style.height="0px";
			 }
		   slot = googletag.defineOutOfPageSlot(unit.s, unit.d).addService(googletag.pubads());
		}
		if (unit.c) {
			slot.addService(googletag.companionAds().setRefreshUnfilledSlots(unit.c));
		}
		if(unitCached && typeof unitCached.sizeMapping!='undefined') {
		   slot.defineSizeMapping(unitCached.sizeMapping);
		}
		tmntag.slots[divId]=slot;
	} else {
		slot = tmntag.slots[divId];
	}

	targets = targets || (unit && unit.g);

	if (targets) for(var k in targets) {
		if (targets.hasOwnProperty(k)) {
			slot.setTargeting(k, targets[k]);
	    }
    }
	if(typeof tmntag.adtargets!='undefined') {
	   var targetData = tmntag.adtargets[unit.d];
		
	   if (typeof targetData!='undefined' && tmntag.localAdtargets && typeof tmntag.localAdtargets[unit.d]!='undefined') {
		   for(var j=0; j<tmntag.localAdtargets[unit.d].length; j++) {
			   targetData.push(tmntag.localAdtargets[unit.d][j]);
		   }
	   }
	   
	   if (refresh && slot) slot.clearTargeting();
	   for(var j=0; slot && typeof targetData!='undefined' && j<targetData.length; j++) {
		 if(targetData[j][0]==='_bd' && targetData[j][1]==='deal') targetData[j][1]='bid';
		 if(typeof tmntag_disablertb!='undefined' && tmntag_disablertb && targetData[j][0]==='_br') continue;
		 slot.setTargeting(targetData[j][0], targetData[j][1]);
	   }
	}
	return slot;
}

var tmntag_setGptLoaded = function () {
	tmntag_gptloaded = true;
}

var tmntag_clientDim=function() {
   try {
      w = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
      h = window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight;
      return w+"x"+h;
   }catch(e){
	   console.error(e);
   }
}
var tmntag_autorefresh=function(divid){
   if (!tmntag.getAdParameters(divid, "auto_refresh_enabled")) return;
   if (typeof tmntag.slots[divid]!='undefined') {
	   var rtb = tmntag.slots[divid].getTargetingMap()['_bd'];
	   if (typeof rtb=='undefined' || rtb!='none') {
		   return;
	   }
   } else {
	   return;
   }
   var adunit = tmntag_getAdunitFromCache(divid);
   var timesRun = adunit['auto_refresh_count'] || 0;
   var dist = 20;
   var refreshLimit=parseInt(tmntag.getAdParameters(divid, "auto_refresh_limit"), 10) || 1;
   var refreshDelay=parseInt(tmntag.getAdParameters(divid, "auto_refresh_delay"), 10) || 60000;
   if (timesRun == refreshLimit) {
       return;
   }
   setTimeout(function () {
      if (tmntag_inview(divid, dist)) {
    	 adunit['auto_refresh_count'] = timesRun+1;
         console.log("-- RAMP -- autoref", divid, adunit['auto_refresh_count']);
         tmntag.refresh(divid);
      }
   }, refreshDelay);
}
var tmntag_inview=function(divid, threshold, mode){
    threshold = threshold || 0;
    mode = mode || 'visible';

    if (document.querySelector("#" + divid) !== null) {
        var rect = document.querySelector("#" + divid).getBoundingClientRect();
        var viewHeight = Math.max(document.documentElement.clientHeight, window.innerHeight);
        var above = rect.bottom - threshold < 0;
        var below = rect.top - viewHeight + threshold >= 0;

        return mode === 'above' ? above : (mode === 'below' ? below : !above && !below);
    }
}
var tmntag_topLocation = function(){
	return (window.context && window.context.location && window.context.location.href)?window.context.location.href:window.top.document.location.href;
}
var tmntag_referrer = function(){
	return (window.context)?window.context.referrer:window.top.document.referrer;
}
tmntag_supportsFlash = function() {
	var supportsFlash = 1;
	try {
		if (navigator.mimeTypes && navigator.mimeTypes.length > 0) {
		    // Firefox, Google Chrome, Safari, Opera
		    var mime = navigator.mimeTypes['application/x-shockwave-flash'];
		    if (mime && mime.enabledPlugin) {
		    	supportsFlash = 1;
		    }
		} else {
		    if (typeof (ActiveXObject) != "undefined") {
		        // Internet Explorer
		        try {
		            var flash = new ActiveXObject("ShockwaveFlash.ShockwaveFlash.1");
		            supportsFlash = 1;
		        }
		        catch (e) {
		        }
		    }
		}
	} catch (e) {
		console && console.error && console.error(exception);
	}
	return supportsFlash;
}
tmntag_gptloaded = false;
tmntag_callbacks = new function(){
	this.callback = [];
	this.callback_executed = [];

	this.pushCallback = function (func, params) {
		if(typeof params !== 'undefined') {
			this.callback.push({'callback' : func, 'params' : params});
		}else{
			this.callback.push({'callback' : func});
		}
	};

	this.executeCallbacks = function() {
		var size = this.callback.length;
		if(size > 0){
			var i = 0;
			while (i<size) {
				var acallback = this.callback[0];
				if(typeof acallback.params !== 'undefined') {
					acallback.callback.apply(null, acallback.params);
				} else {
					acallback.callback();
				}
				this.callback.splice(0, 1);
				this.callback_executed.push(acallback);
				i++;
			}
		}
	};
};
tmntag_il = true;
var tmntag = tmntag || {};
var tmntagCache=[];
tmntag.cmd = tmntag.cmd || [];
tmntagDisplayed={};
tmntag.timing={};
tmntag.timing.adunits={};
tmntag.timing.start=new Date().getTime();
tmntag.sr=true;
tmntag.ced=true;
tmntag.a=[];
tmntag.slots={};
tmntag.l=encodeURIComponent(tmntag_topLocation().replace('%',''));
tmntag.tt=encodeURIComponent(document.title);
tmntag.t=tmntag_timestamp();
tmntag.tz=Math.round(new Date().getTimezoneOffset());
tmntag.r=tmntag_clientDim();
tmntag.su=0;
tmntag.fs=tmntag_supportsFlash();
tmntag.onAdunitRenderedCallbackFunction = function(){};
tmntag.video=tmntag.video||{};
tmntag.video.settings={};
tmntag.video.status={};
tmntag.safeFunctionCall = function(thefunction, defaultValue){
	if (typeof window[thefunction]=='function') return window[thefunction].apply(); 
	else return defaultValue||'';
}
tmntag.placementCustomID = function (placementCustomID) {
	tmntag.pc=placementCustomID;
}
tmntag.getAdParameters = function(div, id) {
	if (typeof div==='undefined') return tmntag && tmntag.adparams;
	else if (typeof id==='undefined') return tmntag && tmntag.adparams && tmntag.adparams[div];
	else return tmntag && tmntag.adparams && tmntag.adparams[div] && tmntag.adparams[div][id];
}
tmntag.placement = function (placementId) {
	tmntag.p=placementId;
}
tmntag.account = function (account) {
	if (account) account = account.replace(/\t|\s+/gm, "");
	tmntag.s=account;
}
tmntag_removeByAttrValue = function(array, attribute, value) {
	for (var i = array.length - 1; i >= 0; i--) {
		var entry = array[i];
		if (entry[attribute] && entry[attribute] === value) {
			array.splice(i, 1);
		}
	}
};
tmntag.adunit = function (adunitObject) {
	var previousAdunitObject = tmntag_getAdunitFromCache(adunitObject.div);
	if (previousAdunitObject) {
		for (prop in adunitObject) {
			previousAdunitObject[prop] = adunitObject[prop];
		}
		adunitObject = previousAdunitObject;
	}
	var a = {};
	if (adunitObject.account) {
		a.s = adunitObject.account;
	} else if (tmntag.s) {
		a.s = tmntag.s;
	}
	if (adunitObject.sizes) {
		a.z = adunitObject.sizes;
	}
	if (adunitObject.div) {
		a.d = adunitObject.div;
	}
	if (adunitObject.targeting) {
		a.g = adunitObject.targeting;
	} else {
		a.g={};
	}
	if (adunitObject.companion) {
        a.c = adunitObject.companion;
    }
	if (adunitObject.div) {
		tmntag_removeByAttrValue(tmntag.a, 'd', adunitObject.div);
		tmntag_removeByAttrValue(tmntagCache, 'div', adunitObject.div);
	}
	if (adunitObject.sizeMapping) {
        a.sm = adunitObject.sizeMapping;
    }
	tmntag.a.push(a);
	tmntagCache.push(adunitObject);
	return a;
}
tmntag.adunitTarget = function (adunitObjectOrID, key, value) {
	if (typeof adunitObjectOrID=='object') {
		adunitObjectOrID.g[key] = value;
	} else if (typeof adunitObjectOrID=='string') {
		tmntag.localAdtargets = tmntag.localAdtargets || [];
		tmntag.localAdtargets[adunitObjectOrID] = tmntag.localAdtargets[adunitObjectOrID] || [];
		tmntag.localAdtargets[adunitObjectOrID].push([key, value]);
	}
}
tmntag.target = function (targetingMap) {
	try {
		if (typeof targetingMap != 'object' || targetingMap instanceof Array) return;
		if (!tmntag.g) {
			tmntag.g = targetingMap;
		}
		for (var key in targetingMap) {
	  		if (targetingMap.hasOwnProperty(key)) {
	  			var value = targetingMap[key];
	  			if (value && tmntag_isArray(value)) {
	  				for (var i=0; i<value.length; i++) {
	  					value[i]=value[i]+"";
	  					value[i] = value[i].replace(/'|;|quot;|39;|&amp;|&|#|\r\n|\r|\n|\t|\f|\%0A|\"|\%22|\%5C|\%23|\%26|\%26|\%09/gm, "");
                        value[i] = value[i].replace(/\%/gm, "");
	  				}
	  				tmntag.g[key.replace(/'|&|#/g, "")]= value;
	  			} else if (value) {
                    key = key.replace(/'|&|#/g, "");
                    value=value+"";
	  				tmntag.g[key]= value.replace(/'|;|quot;|39;|&amp;|&|#|\r\n|\r|\n|\t|\f|\%0A|\"|\%22|\%5C|\%23|\%26|\%26|\%09/gm, "");
                    tmntag.g[key]=tmntag.g[key].replace(/\%/gm, "");
	  			}
			}
		}
	} catch (exception) {
		return console && console.error && console.error(exception);
	}
}
tmntag.location = function (location) {
	tmntag.l = encodeURIComponent(location);
	tmntag.su=1;
}
tmntag.adTag = function (divid, insertDiv) {
	try{
		var unit = tmntag_getAdunitFromCache(divid);
		if(!unit || unit===null) {
			if ((typeof insertDiv=='undefined' || insertDiv ) && !document.getElementById(divid)){
				tmntag_callbacks.pushCallback(tmntag.adTag , [divid, false]);
				if (typeof insertDiv=='undefined') {
				  document.write("<div id=\""+divid+"\"></div>");
				}
			} else if (typeof insertDiv=='undefined') {
				tmntag_callbacks.pushCallback(tmntag.adTag , [divid]);
			} else {
				tmntag_callbacks.pushCallback(tmntag.adTag , [divid, insertDiv]);
			}
			return;
		}
		var dynamic = (typeof unit.adunitRule !== 'undefined' && typeof unit.adunitRule == 'function' && unit.adunitRule(divid) == true);

        if(typeof unit.adunitRule == 'undefined' || dynamic) {
           if ( (typeof insertDiv=='undefined' || insertDiv) && !document.getElementById(divid)) document.write("<div id=\""+divid+"\"></div>");
            /* div exists for sure */
            if (!unit.sizes) {var e = document.getElementById(divid);
               if (e) {e.style.height="0px";}
            }

            tmntag_applyAdunitStyle(divid);

            if (dynamic) {
	            	googletag.cmd.push(function() {
			      if (document.getElementById(divid) && tmntag) {
			    	if (tmntag.slots && !tmntag.slots[divid]) {
			    		if (unit.refresh===1) {
			        		slot = tmntag_defineSlot(divid, {}, true);
			        		unit.refresh = 0;
			        	} else {
			               slot = tmntag_defineSlot(divid);
			        	}
			    	}
			    	var s = new Date().getTime();
					googletag.display(divid);
			      } else {
	                tmntagDisplayed[divid]=1;
			      }

			      /* clone dynamic zones */
				  var dynamicZones = document.querySelectorAll('.purchrtb-dynamic');
				  for(var k = 0, len = dynamicZones.length; k < len; k++) {
					var i = dynamicZones[k].id.lastIndexOf('-');
					var account = '';
					if (i>0) {
					  var origId = dynamicZones[k].id.substring(0, i);
					  var origUnit  = tmntag_getAdUnit(origId);
					  if (origUnit) account = origUnit.s;
					}
					tmntag.adunitClone(divid, dynamicZones[k].id, null, {disableRefreshRamp:1});
					dynamicZones[k].className = '';
				  }
				});
            }else{
				googletag.cmd.push(function() {
				      if (document.getElementById(divid) && tmntag && tmntag.slots && tmntag.slots[divid]) {
				    	var s = new Date().getTime();
						googletag.display(divid);
				      } else {
                      tmntagDisplayed[divid]=1;
				      }
					});
			}
		}
	} catch(exception) {
		return console && console.error && console.error(exception);
	}
};
tmntag.loadScript = function (src, callback, timeout) {
   var canTimeout = typeof timeout !== 'undefined';
   var hasCallback = typeof callback === 'function';
   var s = document.createElement('script');
   s.async = true; s.src = src;
   var h = document.getElementsByTagName('script')[0];
   h.parentNode.insertBefore(s, h);
   var timer;
   var done = function() {
       clearTimeout(timer);
       if (hasCallback) callback();
   };
   if (canTimeout) timer = setTimeout(function(){ done(); }, timeout);
   else if (hasCallback) callback();
};
tmntag_filterAdUnitsByIds = function(divIds, adUnits){
	var filtered = [];
	if (!divIds || !divIds.length) {
		filtered = adUnits;
	} else if (adUnits) {
		var a = [];
		if (!(divIds instanceof Array)) a.push(divIds);
		else a = divIds;
		for (var i = 0, l = adUnits.length; i < l; i++) {
			var adUnit = adUnits[i];
			if (adUnit && adUnit.d && (a.indexOf(adUnit.d) > -1)) {
				filtered.push(adUnit);
			}
		}
	}
	return filtered;
};
tmntag_serializeState = function (refresh, divIds, supportedAdTypes) {
	var state = {};
	if (refresh && supportedAdTypes!=='v') tmntag.f = 1;
	state["f"]  = (refresh)?1:"";
	state["p"]  = (refresh)?"":tmntag["p"];
	state["s"]  = tmntag["s"];
	state["g"]  = tmntag["g"];
	state["l"]  = tmntag["l"];
	state["tt"] = tmntag["tt"];
	state["tt"] = state["tt"].replace(/'|;|quot;|39;|&amp;|&|#|\r\n|\r|\n|\t|\f|\%0A|\"|\%22|\%5C|\%23|\%26|\%26|\%09/gm, "");
	state["fs"] = tmntag["fs"];
	state["a"]  = tmntag_filterAdUnitsByIds(divIds, tmntag.a || []);
	state["t"]  = tmntag_timestamp();
	state["tz"] = Math.round(new Date().getTimezoneOffset());
	state["r"]  = tmntag_clientDim();
	if (refresh && state["a"]) for (var i=0; i<state["a"].length; i++) {
		var adunit = tmntag_getAdunitFromCache(state["a"][i].d);
		if (adunit) adunit.refresh = 1;
	}
    return JSON.stringify(state).replace(/'|&|#/g, "");
};
tmntag_refreshNoWait = function(divIds, targeting) {
	var a = [];
    var at = [];
    if (typeof divIds=='undefined') {
      googletag.pubads().refresh();
      return;
    } else if (divIds instanceof Array){
      for (var id in divIds) {
        var slot = tmntag.slots[divIds[id]];
        if (slot) {
          a.push(slot);
        }
      }
    } else {
      var slot = tmntag.slots[divIds];
      if (slot) {
        a.push(slot);
      }
    }
    if (a.length>0) {
      for (var slot in a) {
        if (targeting) {
          a[slot].clearTargeting();
          for (var key in targeting) {
            if (targeting.hasOwnProperty(key)) {
              a[slot].setTargeting(key, targeting[key]);
            }
          }
        }
      }
      googletag.pubads().refresh(a);
    }
    return console && console.info && console.info("-RAMP- Regular refresh "+divIds);
}
tmntag.refresh = function (divIds, targeting) {
  tmntag.start(true, divIds, function(){tmntag_refreshNoWait(divIds, targeting);}, PREBID_TIMEOUT);
}
tmntag.refreshPixels=function() {
    if(typeof tmntag.tmn_pixels != 'undefined') {
        for(var i=0; i<tmntag.tmn_pixels.length; i++) {
            var pixel = tmntag.tmn_pixels[i];
            if(pixel.isRefreshable()) {
                pixel.execute();
            }
        }
    }
}
tmntag_redirect = function(e, urlormacro, macro) {
   var joinKeys = function(macro){
      var ret = '';
	  if (macro && keys) for (var k in keys) {
         if (keys.hasOwnProperty(k)) {
		    if (macro.hasOwnProperty(keys[k])) {
               if (k==='pd') ret += '&'+k+'=|'+macro[keys[k]]+'|';
               else ret += '&'+k+'='+macro[keys[k]];
            }
		 }
      }
      return ret;
   }
   if (!e) return false;
   var keys = {'cp':'__CP__', 'bdrid':'__BDRID__', 'crid':'__CRID__', 'ad':'__AD__', 'pd':'__PRODUCT_ID__', 'tid': '__TID__'};
   var url = ((typeof urlormacro)==='object')?e.href:urlormacro;
   macro = ((typeof urlormacro)==='object')?urlormacro:macro;
   var rnd = Math.floor(Math.random() * 11000);
   var proto = ('https:'==document.location.protocol)?'https://':'http://';
   var tr = proto+'ramp.purch.com/event.js?t=CL&id='+((top.window.requestid)?top.window.requestid:0)+'&r='+rnd+joinKeys(macro);
   var s = document.createElement('script');
   s.type = 'text/javascript';
   s.src = tr;
   var r = document.getElementsByTagName('script')[0];
   if (r) r.parentNode.insertBefore(s, r);
   var win = window.open(url, '_blank');
   win.focus();
   return false;
}
tmntag.adunitNew = function (adunit) {
	tmntag.adunit(adunit);
	var divid = adunit.div;
	var slot = tmntag_defineSlot(divid);
	googletag.display(divid);
	tmntag.refresh(divid);
}
tmntag.adunitClone = function (divId, cloneDivId, targets, parameters) {
   var incAccountKey = function(adunit, key) {
      if (adunit) {
         var ac = adunit['account'];
         if (ac) {
            var a = ac.split('/');
            if (a && a.length>0) {
               var aa = a.reverse()[0];
               if (aa.indexOf("-")>0) {
            	   var ar = aa.split('-');
            	   if (ar && ar.length>0) for (var i=0; i<ar.length; i++) {
            		   var ari=ar[i];
            		   if (ari.indexOf(key)==0) {
            			   var idx = ari.substring(1);
            			   if (!isNaN(idx)) {
            				   var idx = (idx*1)+1;
            				   ar[i] = key+idx;
                           }
                       }
            	   }
                   var newAcct = ar.join('-');
                   a[0] = newAcct;
                   adunit['account'] = a.reverse().join('/');
                }
            }
         }
      }
   };
   var incPosition = function(adunit) {
	   var targetingData = unitClone.targeting || {};
	   for (var k in targetingData) {
       if (targetingData.hasOwnProperty(k) && k==='_p' && targetingData[k]) {
    	   unitClone.targeting[k] = (1*targetingData[k])+1;
       }
     }
   }
  if ('JSON' in window) {
	  var origUnit = tmntag_getAdunitFromCache(divId);
	  if (origUnit) {
		  var unitClone;
	      try { unitClone = JSON.parse(JSON.stringify(origUnit)); } catch (e) { return false; }
	      unitClone.div = cloneDivId;
	      unitClone.targeting = unitClone.targeting || {};
	      if (targets) for (var k in targets) {
	    	  if (targets.hasOwnProperty(k)) {
	    		  unitClone.targeting[k] = targets[k];
	    	  }
	      }
	      if (!parameters || !parameters['disableIncrementAccountPosition']) {
	    	  incAccountKey(unitClone, 'p');
	      }
	      if (!parameters || !parameters['disableIncrementPosition']) {
	    	  incPosition(unitClone);
	  	  }
	      tmntag.adunit(unitClone);
          if (origUnit.adunitRule) {
            if (tmntag.getAdParameters(divId) && tmntag.getAdParameters(divId)['on_clone_execute_preadunitrender'] === 'true') {
              origUnit.adunitRule.apply(this, [cloneDivId]);
            }
          }
	      var slotClone = tmntag_defineSlot(cloneDivId, unitClone.targeting);
	      if (!parameters || !parameters['disableRefreshRamp']) {
	    	  tmntag.start(true, cloneDivId, function(){
		    	  googletag.cmd.push(function () {
			    	  googletag.display(cloneDivId);
			    	  if(typeof tmntag_il !== 'undefined' && tmntag_il == false) {
			    		  googletag.pubads().refresh([slotClone]);
			    	  }
			      });
		      }, PREBID_TIMEOUT);
	      } else {
	    	  googletag.cmd.push(function () {
		    	  googletag.display(cloneDivId);
		    	  if(typeof tmntag_il !== 'undefined' && tmntag_il == false) {
		    		  googletag.pubads().refresh([slotClone]);
		    	  }
	    	  });
	      }
	      return slotClone;
	  }
  }
  return false;
}
tmntag.disableSingleRequest = function() {
	tmntag.sr = false;
}
tmntag.disableCollapseEmptyDivs = function() {
	tmntag.ced = false;
}
tmntag.enableSingleRequest = function() {
	tmntag.sr = true;
}
tmntag.disableInitialLoad = function() {
	// tmntag_il = false;
}
tmntag.disableCollapseEmptyDivs = function() {
	tmntag.ced = false;
}
tmntag.onInlineAdunitRendered = function(event) {
	var divid = event.divid;
	var adunit = tmntag_getAdunitFromCache(divid);
	var newEvent = {};
	newEvent['div'] = divid;
	newEvent['adunit'] = adunit;
	if (event.size) newEvent['size'] = {width: event.size[0], height: event.size[1]};
    else newEvent['size'] = {width: 0, height: 0};
	newEvent['isEmpty'] = false;
	newEvent['dfpCreativeId'] = "";
	newEvent['dfpLineItemId'] = "";
	adunit['dfpCreativeId'] = "";
	adunit['dfpLineItemId'] = "";
	newEvent['_orig'] = event;
	tmntag_registerMouseOver(divid);
	tmntag.onAdunitRenderedCallbackFunction(newEvent);
	if (adunit
		&& adunit['onAdunitRendered']
	    && typeof adunit['onAdunitRendered'] === 'function') {

		adunit['onAdunitRendered'](event);
	}
	if (typeof tmntag_adlabel!='undefined' && tmntag_adlabel) {
		tmntag_adlabel.render(divid, newEvent);
    }
	tmntag.timing.adunits[divid]={'onAdunitRendered':(new Date().getTime()-tmntag.timing.start)};
}
tmntag.onAdunitRenderedPrivate = function(event) {
	var divid = event.slot.getSlotId().getDomId();
	var adunit = tmntag_getAdunitFromCache(divid);
	var newEvent = {};
	newEvent['div'] = divid;
	newEvent['adunit'] = adunit;
	if (event.size) newEvent['size'] = {width: event.size[0], height: event.size[1]};
    else newEvent['size'] = {width: 0, height: 0};
	newEvent['isEmpty'] = event.isEmpty;
	newEvent['dfpCreativeId'] = event.creativeId;
	newEvent['dfpLineItemId'] = event.lineItemId;
	adunit['dfpCreativeId'] = event.creativeId;
	adunit['dfpLineItemId'] = event.lineItemId;
	newEvent['_orig'] = event;
	tmntag_registerMouseOver(divid);
	tmntag.onAdunitRenderedCallbackFunction(newEvent);
	if (adunit
		&& adunit['onAdunitRendered']
	    && typeof adunit['onAdunitRendered'] === 'function') {

		adunit['onAdunitRendered'](event);
	}
	if (typeof tmntag_adlabel!='undefined' && tmntag_adlabel) {
		tmntag_adlabel.render(divid, newEvent);
    }
	tmntag.timing.adunits[divid]={'onAdunitRendered':(new Date().getTime()-tmntag.timing.start)};
	tmntag.timing.adunits[divid].startRendered = new Date();
	tmntag_autorefresh(divid);
}
tmntag.onAdunitViewablePrivate = function(event) {
	var divid = event.slot.getSlotId().getDomId();
	var adunit = tmntag_getAdunitFromCache(divid);
	adunit['viewable']=true;

}
tmntag.onAdunitRendered = function(callback) {
    callback = typeof callback === 'function' ? callback : function() {};
    tmntag.onAdunitRenderedCallbackFunction = callback;
}
tmntag_executingStart = false;
tmntag.start = function (refresh, divIds, callback, timeout, tmntagVersion, supportedAdTypes) {
	var startPrivate = function (refresh, divIds, callback, timeout) {
		if (!refresh) {
			tmntag.enableSingleRequest();
			googletag.cmd.push(function() {
			   googletag.pubads().addEventListener('slotRenderEnded', function(event) {
			      tmntag.onAdunitRenderedPrivate(event);
			   });
			   googletag.pubads().addEventListener('impressionViewable', function(event) {
	              tmntag.onAdunitViewablePrivate(event);
		       });
			});
		}
		if (tmntag_executingStart && !refresh) return;
		tmntag_executingStart = true;
		var i, r = Math.floor(Math.random() * 11000);
   		var host = tmntag_findURL();
   		var jsBids = [];
   		if (typeof amznads!='undefined' && amznads != null && typeof amznads.getTokens==='function') {
      		var allBids = amznads.getTokens();
      		if (allBids!=null && allBids.length>0) {
      			var a = allBids.join();
      			a = a.replace('kindle_pur_3x6', 'a3x6p100');
         		jsBids.push({'br':6, 'bs':a});
      		}
   		}
	   	if (typeof prebidSlots === 'object' && prebidSlots != null) {
	   		for(var bidderId in prebidSlots) {
	   			if(prebidSlots.hasOwnProperty(bidderId)) {
	   				var bidderSlots = prebidSlots[bidderId];
	   				var bidderBids = [];
	   				for (i in bidderSlots) {
	   					var prebidUnit = bidderSlots[i];
	   					if (typeof prebidUnit === 'object') {
	   	   				   	bidderBids.push('a'+prebidUnit.width+"x"+prebidUnit.height+'p'+prebidUnit.cpm+':'+prebidUnit.ad);
	   	   			   	}
	   				}
	   		   	   	if (bidderBids.length > 0) {
	   			   		jsBids.push({'br':bidderId, 'bs':bidderBids.join()});
	   		   		}
	   	    	}
	   		}
	   	}

		var qs = "r="+r+"&o="+tmntag_serializeState(refresh, divIds, supportedAdTypes);
		if (jsBids.length>0) {
        	qs += "&j="+JSON.stringify(jsBids);
      	}

		if (!tmntagVersion) tmntagVersion=TMNTAG_VERSION;
		if (supportedAdTypes) qs += "&at="+supportedAdTypes;
		else qs += "&at=bnj";
		if (!refresh) {
			tmntag.timing.loadTag=(new Date().getTime());
			tmntag.cmd.push(function(){tmntag.loadScript(host+"tmntag.js?v="+tmntagVersion+"&"+qs);});
		} else {
	        tmntag.loadScript(host+"tmntag.js?v="+tmntagVersion+"&"+qs, callback, timeout);
		}
	}

	if (refresh) {
		amznads = null;
		if (pbjs && typeof pbjs.startPrebids == 'function') {
			pbjs.initAdserverSet = false;
			prebidSlots = [];
			prebidAds = {};
			pbjs.adUnits = [];
			pbjs.startPrebids();
		}
	}
	setTimeout(function(){startPrivate(refresh, divIds, callback, timeout);}, PREBID_TIMEOUT);
}
tmntag_findURL = function () {
   for (var i=0; i<document.scripts.length; i++) {
      var script = document.scripts[i];
      var idx = script.src.indexOf('tmnhead.js');
      if (idx>0) {
         return(script.src.substring(0, idx));
      }
   }
   return 'http://ads.servebom.com/';
}
tmntag_passback = function (doc, id) {
	if (!id) return;
	var a = id.split("|");
	if (a.length==1) {
		var ret = tmntag_render(doc, id);
	} if (a.length>=4) { /* adunit|WIDTH|HEIGHT|adslot */
		var ret = tmntag_render(doc, a[0]);
		if (!ret) {
			doc.write('<scr'+'ipt type="text/javascript">google_ad_client = "ca-pub-5787592483766760";'
					+'\ngoogle_ad_slot = \"'+a[3]+'\";'
					+'\ngoogle_ad_width = '+a[1]+';'
					+'\ngoogle_ad_height = '+a[2]+';'
					+'</scr'+'ipt>'
					+'<scr'+'ipt type="text/javascript" src="//pagead2.googlesyndication.com/pagead/show_ads.js"></scr'+'ipt>');
		}
	}
}
tmntag_applyAdunitStyle = function(divid){
  adParams = tmntag.getAdParameters(divid);
  if (!adParams) return;
  var styleParams = adParams['adunit_style'];
  if (styleParams) {
    var adunit = document.getElementById(divid);
    styleParams = styleParams.trim().split(';');
    for (var i = 0; i < styleParams.length; i++) {
      if(styleParams[i] === ''){continue;}
      style = styleParams[i].split(':')
      var importance = null;
      if (!style[1]){continue;}
      if (style[1].indexOf('!important') >= 0) {
        style[1] = style[1].replace('!important', '');
        importance = 'important';
      }
      adunit.style.setProperty(style[0].trim(),style[1].trim(),importance);
    }
  }
}
tmntag.video.logError=function(event){
	console.log("-RAMP VIDEO- Error", event);
}
tmntag.video.logImpression=function(event){
	console.log("-RAMP VIDEO- Impression", event);
}
tmntag.video.start=function(divid, videoSettings, videoPlayer, adunitDivid, enableSetup) {
	if (typeof videoSettings.advertising=='undefined' || !videoSettings) videoSettings.advertising = {client:"googima"};
    /*videoSettings.advertising["vpaidmode"]="enabled";*/
	videoSettings.advertising.autoplayadsmuted=true;
	videoSettings.advertising.vpaidcontrols=true;
	if (typeof adunitDivid=='undefined' || !adunitDivid) adunitDivid = divid;
	if (enableSetup) videoPlayer.setup(videoSettings);
	tmntag.video.status[divid] = {};
	tmntag.video.status[divid].errors = [];
	tmntag.video.status[divid].impressions = [];
	tmntag.video.status[divid].player_settings = videoSettings;
	tmntag.video.status[divid].player = videoPlayer;
	jwplayer().on('adError', function(event) {
	   tmntag.video.logError(event);
       tmntag.video.status[divid].errors.push(event);
    });
	jwplayer().on('adImpression', function(event) {
	   tmntag.video.logImpression(event);
	   tmntag.video.status[divid].impressions.push(event);
    })
    videoPlayer.on("playlistItem", function() {
      videoPlayer.once("beforePlay", function(){
    	if (typeof tmntag.video.status[divid].fetch_count=='undefined') tmntag.video.status[divid].fetch_count=0;
    	tmntag.videoRefresh(divid);
    	videoPlayer.pause(true);
    	setTimeout(function(){
    		var tag = tmntag.video.adTag(adunitDivid, videoPlayer.id);
            console.log("-RAMP VIDEO- fetch count: "+tmntag.video.status[divid].fetch_count+" tag:"+tag);
    		videoPlayer.playAd(tag);
    		tmntag.video.status[divid].fetch_count++;
            tmntag.video.status[divid].tag = tag;
    	}, VIDEO_REFRESH_TIMEOUT);
      });
    });
}
tmntag.video.adTag=function(divid, playerId){
	var adunitAccount = '';
	var adunit = tmntag_getAdunitFromCache(divid);
	if (adunit && adunit.account) {
		adunitAccount = adunit.account;
	} else {
		var a = tmntag_getAdUnit(divid);
		if (a && a.s) {
			adunitAccount = a.s;
		} else {
			return "";
		}
	}
	var pageUrl;
	if (tmntag.l && tmntag.su==1) pageUrl = tmntag.l.replace('%','');
	else pageUrl = encodeURIComponent(tmntag_topLocation().replace('%',''));

	var videoTitle = "__item-title__";
	var vadtargets = tmntag.vadtargets;
	var pubtargets = tmntag.pubtargets;
	var dfpParams = ["sz=640x480", "iu="+adunitAccount, "ciu_szs=728x90,300x250", "impl=s", "gdfp_req=1", "env=vp"
	                 , "output=xml_vast3", "unviewed_position_start=1"
	                 , "url="+pageUrl, "correlator=__timestamp__"];
	var dfpCustParams = ["plID="+playerId, "ttID=__item-mediaid__", "vdbl=yes"
	                     , "vvid_title="+videoTitle
	                     , "pos=preroll"];
	// __page-url__
	var dfpUrl = "https://pubads.g.doubleclick.net/gampad/ads";
	var found = false;
	if (typeof pubtargets!='undefined') {
		for (var k in pubtargets) {
			dfpCustParams.push(pubtargets[k][0]+"="+pubtargets[k][1]);
		}
	}
	if(typeof vadtargets!='undefined') {
	  for (var k in vadtargets) {
	    var targetData = vadtargets[k];
	    for(var i=0; typeof targetData!='undefined' && i<targetData.length; i++) {
	      if (targetData[i][0]==="_vst") {
	        var val = targetData[i][1];
	        val = val.split("/");
	        if (val.length>1) {
	          var v = val[val.length-2]+"/"+val[val.length-1];
	          dfpCustParams.push("_vst="+v);
	        }
	      } else {
	        dfpCustParams.push(targetData[i][0]+"="+targetData[i][1]);
	      }
	      found = true;
	    }
	    if (found) {
	      break;
	    }
	  }
	  tmntag.vadtargets=[];
	}
	return dfpUrl+"?"+dfpParams.join("&")+"&cust_params="+encodeURIComponent(dfpCustParams.join("&"));
}
tmntag.videoRefresh = function (divIds) {
  console.log("-RAMP VIDEO- Refresh");
  tmntag.start(true, divIds, function(){}, PREBID_TIMEOUT, TMNTAGVIDEOREFRESH_VERSION, "v");
};
tmntag_render = function (doc, id) {
    var ret = false;
    if (typeof tmntag.markups!='undefined') {
        var markup = tmntag.markups[id];

        if (typeof markup!='undefined' && markup!=null) {
            markup = markup.replace('a3x6p100', 'kindle_pur_3x6');
            markup = markup.replace(/'\r\n|\r|\n/gm, "");

            if (tmntag_checkIfLazyLoaded(id)) {
                var listener = tmntag_debounce(function () {
                    if (tmntag_inview(id)) {
                        document.removeEventListener('scroll', listener);
                        tmntag_writeToDocument(doc, id, markup);
                    }
                }, 50);
                document.addEventListener('scroll', listener);
                listener();
            } else {
                tmntag_writeToDocument(doc, id, markup);
                ret = true;
            }
        }
    }
    return ret;
};
tmntag_checkIfLazyLoaded = function (id) {
    var displayInView = false;
    if ('undefined' !== typeof tmntag.adtargets && 'undefined' !== typeof tmntag.adtargets[id]) {
        tmntag.adtargets[id].forEach(function (property) {
            displayInView = displayInView || (property[0] === '_ll' && property[1]);
        });
    }
    return displayInView;
};
tmntag_writeToDocument = function (doc, id, markup) {
    doc.write(markup);

    var slot = tmntag.slots[id];
    if (slot) {
        slot.setTargeting("_bd", "none");
    }

    if (doc.defaultView && doc.defaultView.frameElement) {
        var width = tmntag.markupsInfo[id]['width']+"px";
        var height = tmntag.markupsInfo[id]['height']+"px";
        doc.defaultView.frameElement.width = width;
        doc.defaultView.frameElement.height = height;
        if (tmntag_inIframe() && self && self.frameElement) {
            self.frameElement['width'] = width;
            self.frameElement['height'] = height;
        }
    }
};
tmntag_debounce = function (func, wait, immediate) {
    var timeout;
    return function () {
        var context = this, args = arguments;
        var later = function() {
            timeout = null;
            if (!immediate) func.apply(context, args);
        };
        var callNow = immediate && !timeout;
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
        if (callNow) func.apply(context, args);
    };
};
tmntag_ready( function() {
	if (tmntag) for (var i=0; i<tmntag.a.length; i++) {
		tmntag_inlineMarkup(tmntag.a[i].d);
	}
}
);
tmntag.cmd.executeCommands = function() {
   while (i = tmntag.cmd.shift()) {
      if (typeof i==='function') {i();}
   }
}
tmntag.cmd.push = function(item) {
   tmntag.cmd.executeCommands();
   if (typeof item==='function') {item();}
}
tmntag.cmd.pushDefined = true;

var tmntag_checkCommands = function() {
   if (!tmntag.cmd.pushDefined) {
      setTimeout(tmntag_checkCommands, 100);
   } else {
      tmntag.cmd.executeCommands();
   }
}
tmntag_checkCommands();
tmntag.apiReady=true;
tmntag.timing.endHead=new Date().getTime();
tmntag.timing.debug=function(showRAMPTiming) {
	var all={};
	all.timing={};
	if (showRAMPTiming && tmntag.timing) {
	   all.timing.ramp={};
	   all.timing.ramp.head=tmntag.timing.endHead-tmntag.timing.start;
	   all.timing.ramp.loadTag=tmntag.timing.loadTag-tmntag.timing.start;
	   all.timing.ramp.startTag=tmntag.timing.startTag-tmntag.timing.loadTag;
	   all.timing.ramp.googleEnableServices=tmntag.timing.endEnableServices-tmntag.timing.startEnableServices;
	   all.timing.ramp.endTag=tmntag.timing.endTag-tmntag.timing.startTag;
	   all.timing.ramp.total=tmntag.timing.endTag-tmntag.timing.start;
	}
	if (window.performance) {
	   all.timing.ttfb=window.performance.timing.responseStart-window.performance.timing.requestStart;
	   all.timing.ttlb=window.performance.timing.responseEnd-window.performance.timing.responseStart;
	   all.timing.ttsr=window.performance.timing.domInteractive-window.performance.timing.responseEnd;
	}
	return all;
}
tmntag.debug=function() {
	var all={};
	all.TMNAPI_VERSION=TMNAPI_VERSION;
	all.PREBID_TIMEOUT=PREBID_TIMEOUT;
	all.TMNTAG_VERSION=TMNTAG_VERSION;
	all.timing=tmntag.timing.debug();
	all.googletag=(typeof googletag!='undefined')?googletag:'none';
	all.pbjs=(typeof pbjs!='undefined')?pbjs:'none';
	all.initialLoadEnabled=tmntag_il;
	all.singleRequestEnabled=tmntag.sr;
	all.collapseEmptyDivs=tmntag.ced;
	all.tmntag=tmntag;
	all.tmntagCache=tmntagCache;
	all.tmntagDisplayed=tmntagDisplayed;
	all.adunits=tmntag.a;
	all.googleSlots=tmntag.slots;
	all.pageLoation=tmntag_topLocation();
	all.now=tmntag.t;
	all.timeZone=tmntag.tz;
	all.browserDim=tmntag.r;
	all.adParameters=tmntag.adparams;
	all.placement=tmntag.p;
	all.amazonAds=(typeof amznads!='undefined')?amznads:'none';
	all.prebidSlots=(typeof prebidSlots!='undefined')?prebidSlots:'none';
	all.prebidAds=(typeof prebidAds!='undefined')?prebidAds:'none';
	all.target=(typeof tmntag.pubtargets!='undefined')?tmntag.pubtargets:'none';
	all.adunitTarget=(typeof tmntag.adtargets!='undefined')?tmntag.adtargets:'none';
	all.adMarkups=(typeof tmntag.markups!='undefined')?tmntag.markups:'none';
	return all;
}
/* Incontent */
var PurchInContent = function(divId) {
   var onlyText = function($elem) {
      // remove sub scripts tags
      return $elem.clone().find('script').remove().end().text().trim().length;
   };

   this.isvisible = function(divId) {

      return (onlyText($("#news-content > p")) >= 1350 &&
         $("#news-content .shopping_generic, #news-content .responsiveTable, #news-content .responsiveTableCompact, #news-content .shopping_cpu, #news-content .shopping_gpu, #news-content shopping_ssd").length === 0
      ) || ($(".inContentAd").length > 0);
   };

   this.createZone = function(divId) {
      if ($(".inContentAd").length > 0) {
         return MultipleIncontent(divId, ".inContentAd");
      }
      var minChars = $('body').hasClass('mobile') ? 500 : 1000;
      $("#news-content > p").each(function(index) {
         var current = onlyText($("#news-content > p:eq(" + index + ")"));
         if ((onlyText($("#news-content > p:lt(" + index + ")")) + current) >= minChars && onlyText($("#news-content > p:gt(" + index + ")")) >= 350) {
            $("#news-content > p:eq(" + index + ")").after($('<div id=' + divId + ' class="zonepub zonepub17"></div>'));
            //We break the each() loop
            return false;
         }
      });
   };
   var res;
   if (res = this.isvisible(divId)) {
      this.createZone(divId);
   }

   return res;
}
/* Multiple Incontent */
var MultipleIncontent = function(divId, selectors) {
   this.insertAfter = function insertAfter(newNode, referenceNode) {
      referenceNode.parentNode.insertBefore(newNode, referenceNode.nextSibling);
   };
   // Place target divs (source + clones), and return rule validation
   if (!divId || !selectors) {
      return false;
   }
   var aTarget = document.querySelectorAll(selectors);
   // place div source if not already done
   if (aTarget.length) {
      for (var i = 0, len = (aTarget.length); i < len; i++) {
         if (i == 0) {
            var newDiv = document.getElementById(divId);
            if (!newDiv) {
               newDiv = document.createElement('div');
            }
            newDiv.id = divId;
            this.insertAfter(newDiv, aTarget[i]);
         } else {
            var newId = divId + '-' + i + (new Date().getTime());
            var newDivC = document.createElement('div');
            newDivC.id = newId;
            newDivC.className = 'purchrtb-dynamic';
            this.insertAfter(newDivC, aTarget[i]);
         }
      }
   }
   return document.querySelectorAll(selectors).length > 0;
};
/* /Purch Ad Tag API V5.4.23 Copyright 2017 Purch, Inc.*/
tmntag.floorprices={};
tmntag.headerbidderstodrop={};
tmntag.incontent = tmntag.incontent || function(divId, selector, position) {
   if (!divId || !selector) { return false; }
   var target = document.querySelector(selector);
   if (target) {
	   var newDiv = document.getElementById(divId);
       if (!newDiv) {
          newDiv = document.createElement('div');
          newDiv.id = divId;
       }
       if (typeof position=='undefined') position = 'afterend';
       
       if (position === 'prepend') {
         target.insertBefore(newDiv, target.firstChild);
       } else {     
         target.insertAdjacentElement(position, newDiv);
       }
       return newDiv;
   }
   return false;
};

var amznads=amznads||{};
if(!tmntag_inIframe()&&(tmntag_IEVersion()==-1||tmntag_IEVersion()>=9))try{aaxID="3150";if(aaxID!=""&&aaxID.indexOf("$")!=0){amznads.asyncParams={id:aaxID,callbackFn:function(){},timeout:PREBID_TIMEOUT};(function(){if(document.location.href.indexOf("_noaax=1")>0)return;var a,b=document.getElementsByTagName("script")[0];a=document.createElement("script");a.type="text/javascript";a.async=true;a.src="//c.amazon-adsystem.com/aax2/amzn_ads.js";b.parentNode.insertBefore(a,b)})()}}catch(a){console&&
console.error&&console.error(a)};


function PurchStickyColumn(divid, params) {

  if (window.innerWidth > 810) {
    
    var div       = params && params['colElement']; 
    var stop      = params && params['stopElement'];
    var article   = params && params['artElement'];
    var topMargin = params && params['topMargin'] || 10;
	var pixels    = params && params['distance'];
	var bgColor    = params && params['bgColor'];

   
	if (div) var o = document.querySelector(div);
	
	var colProps = window.getComputedStyle((o), null);
	var truHeight = colProps.getPropertyValue('height');

	var numHeight = parseInt(truHeight, 10);

	var pixelNum = parseInt(pixels, 10);
	
	var n = o.offsetTop;
	var	d = o.offsetLeft;
	var	i = numHeight;
		
	var h = document.querySelector(article);
	var a = h.offsetHeight;
	
	var stopDiv = document.querySelector(stop);
	var stopTop = stopDiv.offsetTop;
	
	var l,s;
	  
	if (stop) {
        l = document.querySelector(stop);
		if(l){ s = l.offsetTop - i - 20;}
	}
	
	if (pixels) {
		if (pixelNum) { var p = n + pixelNum;}
	}
			  
    if (stopTop < i || stopTop < p || a < (i + p)) {
      return false;
    }

	var winWidth = window.innerWidth;
	
	if (window.addEventListener) {
	  window.addEventListener('resize', function() {
		var newWinWidth = window.innerWidth;
		d += (newWinWidth - winWidth) / 2;
		winWidth = newWinWidth;
		o.style.left = d + 'px';
	  }, true);
	} else {
	  window.attachEvent("resize", function() {
		var newWinWidth = window.innerWidth;
		d += (newWinWidth - winWidth) / 2;
		winWidth = newWinWidth;
		o.style.left = d + 'px';
	  })
	}
	
	if (window.addEventListener) {
      window.addEventListener("scroll", function() {
			var e = void 0 !== window.pageYOffset ? window.pageYOffset : (document.documentElement || document.body.parentNode || document.body).scrollTop;
	
		if (pixels && e > p) {
            var t = e - p;
			o.style.position = "fixed", o.style.top = 0 - Math.floor(t) + 10 + "px", o.style.left = d + "px", o.style.background = "transparent"
			
        } else if (stop && e > s) {
			var t = e - s;
			o.style.position = "fixed", o.style.top = 0 - Math.floor(t) + 10 + "px", o.style.left = d + "px", o.style.background = "transparent"
			
		 } else e > n - 20 ? (o.style.position = "fixed", o.style.top = topMargin + "px", o.style.left = d + "px", o.style.background = bgColor) : (o.style.top = "", o.style.position = "static", o.style.left = d + "px", o.style.background = "transparent")
			
		})
	} else {
      window.attachEvent("scroll", function() {
		var e = void 0 !== window.pageYOffset ? window.pageYOffset : (document.documentElement || document.body.parentNode || document.body).scrollTop;
		if (pixels && e > p) {
            var t = e - p;
			o.style.position = "fixed", o.style.top = 0 - Math.floor(t) + 10 + "px", o.style.left = d + "px", o.style.background = "transparent"
			
        } else if (stop && e > s) {
			var t = e - s;
			o.style.position = "fixed", o.style.top = 0 - Math.floor(t) + 10 + "px", o.style.left = d + "px", o.style.background = "transparent"
			
		 } else e > n - 20 ? (o.style.position = "fixed", o.style.top = topMargin + "px", o.style.left = d + "px", o.style.background = bgColor) : (o.style.top = "", o.style.position = "static", o.style.left = d + "px", o.style.background = "transparent")
			
      })
    }
    
  }

}
