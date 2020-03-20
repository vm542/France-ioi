$(function() {
   initMainTabs();
   initCodeTabs();
   initSimu();
   initActivity();
});


function initMainTabs() {
   var me = $("#thread-tabs");
   var ul = $("<ul>");
   me.children("div").each(function(index) {
      var id = $(this).attr('id');
      var title = $(this).attr('data-header');
      $(ul).append('<li><a href="#' + id + '">' + title + '</li>');
   });
   me.prepend(ul);
   me.tabs();
}


function initCodeTabs() {
   $("div.codeTabs").each(function() {
      var me = $(this);

      var ul = $("<ul>");
      $(this).children("div").each(function (index)
      {
         $(this).attr('id', 'tabs-'+index);
         var title = $(this).attr('title');
         var lang = $(this).attr('lang');
         if (typeof title === 'undefined' || title === false || title === '')
            title = lang;
         $(ul).append('<li><a href="#tabs-'+index+'">'+lang+'');
      });
      me.prepend(ul);

      me.tabs();   	

      var allDivs = $(this).children("div").get().reverse();
      $(allDivs).each(function(index) {
         sLang = sSelectedLanguage;
         if(sLang == 'Cpp')
            sLang = "C++";
         if ($(this).attr('lang') == sLang)
            me.tabs('select', allDivs.length - 1 - index);
      });
   });
}


function initSimu() {
   if (typeof simulationInstance === "undefined") return;

   var simuNum = 1;
   $('.evaluation-results-table').each(function() {
      var nbBad = $(this).find('.evaluation-result-error, .evaluation-result-failure, .evaluation-result-perffail').length;
      var fe = $(this).find('.evaluation-result-' + (nbBad == 0 ? 'success' : 'failure') + ' pre').eq(0);

      if (fe.length > 0) {
         var json = fe.html();
         var td = fe.parent();

         try {
            $.parseJSON(json);
            var idSimu = 'simuTest' + simuNum;
            td.html($('<div>').attr('id', idSimu));
            instance = createInstance(idSimu, json, {
               reset: false,
               play: false,
               replay: true,
            });
            instance.startSimulation();
         }
         catch(e) {}
         simuNum++;
      }
      $(this).find('.evaluation-result-failure pre, .evaluation-result-success pre').remove();
   });
}


function setCookie(key, value) {
   document.cookie = key + '=' + value + ';';
}
function getCookie(key) {
   var keyValue = document.cookie.match('(^|;) ?' + key + '=([^;]*)(;|$)');
   return keyValue ? keyValue[2] : null;
}

var floatingTextarea = null;

function reloadActivity() {
   $.get($('.navigbox a:last').attr('href') + '&sView=onlyActivity&sOnlyBlock=mainContent', function(result) {
      var oldActivity = $('.thread-contents');
      var newActivity = $(result).find('.thread-contents');
      oldActivity.find('.toggleHeader').each(function() {
         newActivity.find('#' + $(this).attr('id')).prop('checked', $(this).prop('checked'));
      });
      if (floatingTextarea !== null) {
         var newMessage = newActivity.find('#' + floatingTextarea.attr('data-message')).next();
         newMessage.find('.thread-message-contents').addClass('hide');
         newMessage.find('form').replaceWith(oldActivity.find('#' + floatingTextarea.attr('data-message')).next().find('form'));
      }
      oldActivity.replaceWith(newActivity);
      SyntaxHighlighter.highlight();
      initSimu();
      if (floatingTextarea !== null) {
         var formTextarea = $('#' + floatingTextarea.attr('data-message')).next().find('.thread-write');
         var formTextareaPos = formTextarea.position();
         floatingTextarea.css({
            left: formTextareaPos.left + 'px',
            top: formTextareaPos.top + 'px',
            width: formTextarea.outerWidth() + 'px',
         }).resize();
      }
   });
}

function waitForEvalResults(divRes, resultUrl) {
   var retryDelay = 1000;
   var lookForEval = function() {
      var finished = false;
      $.ajax({
         type: 'GET',
         url: resultUrl,
         async: false,
         success: function(result) {
            var content = $(result).find('#eval_results').html();
            if (content.length != 0) {
               finished = true;
            }
         },
         error: function(XMLHttpRequest, textStatus, errorThrown) {
            alert("La réévaluation n'a pas pu être effectuée : le serveur n'a pas renvoyé de réponse valide.");
            finished = true;
         }
      });
      if (!finished) {
         retryDelay *= 2;
         if (retryDelay > 300000) {
            alert("L'évaluation n'a pas été effectuée à temps. Essayez de réévaluer la soumission dans l'onglet Activité.");
            $.unblockUI();
         } else {
            setTimeout(lookForEval, retryDelay);
         }
      } else {
         $.unblockUI();
         divRes.text("…");
         reloadActivity();
      }
   };
   lookForEval();
}

function initActivity() {
   // Restauration du message enregistré pour la discussion, s’il y en a un
   var cookieName = 'forumMessage_t' + idThread;
   var message = getCookie(cookieName);
   if (message) {
      message = decodeURIComponent(message);
      if ($('.thread-message-source:last').text() != message) {
         $('#newMessage').val(message);
      }
   }

   // Enregistrement régulier du message en cours d’écriture
   setInterval(function() {
      setCookie(cookieName, encodeURIComponent($('#newMessage').val() || ''));
   }, 3000);

   // Modification d’un message déjà posté, en utilisant un champ texte flottant pour éviter qu’il soit écrasé par un rechargement
   $(document).on('click', '.thread-message-details .edit', function() {
      var parentMessage = $(this).closest('.thread-message');
      parentMessage.find('.thread-message-contents, form').toggleClass('hide');
      if (parentMessage.find('form').hasClass('hide')) {
         floatingTextarea.remove();
         floatingTextarea = null;
      } else {
         var formTextarea = parentMessage.find('.thread-write');
         if (floatingTextarea !== null) {
            $('#' + floatingTextarea.attr('data-message')).next().find('.thread-message-contents, form').toggleClass('hide')
               .find('[tabindex]').removeAttr('tabindex');
            floatingTextarea.remove();
         }
         floatingTextarea = formTextarea.clone();
         floatingTextarea.val(formTextarea.val()).attr('data-message', parentMessage.prev().attr('id'));
         var formTextareaPos = formTextarea.position();
         $('.thread-contents').before(floatingTextarea);
         formTextarea.focus(function() {
            floatingTextarea.focus();
         });
         floatingTextarea.css({
            position: 'absolute',
            left: formTextareaPos.left + 'px',
            top: formTextareaPos.top + 'px',
            width: formTextarea.outerWidth() + 'px',
            height: formTextarea.outerHeight() + 'px',
            'z-index': 1
         }).focus(function() {
            var formTextareaPos = $('#' + floatingTextarea.attr('data-message')).next().find('.thread-write').position();
            floatingTextarea.css({
               left: formTextareaPos.left + 'px',
               top: formTextareaPos.top + 'px'
            });
         }).blur(function() {
            $('#' + floatingTextarea.attr('data-message')).next().find('.thread-write').val(floatingTextarea.val());
         }).on('resize mouseup', function() {
            $('#' + floatingTextarea.attr('data-message')).next().find('.thread-write').height(floatingTextarea.height());
         }).attr('tabindex', 1).focus();
         var elem = formTextarea;
         for (var tabIndex = 2; tabIndex <= 4; tabIndex++) {
            elem = elem.next().attr('tabindex', tabIndex);
         }
      }
      return false;
   });

   // Rechargement automatique du contenu
   if ($('.thread-item').length < 100 && $('.thread-contents').html().length < 500 * 1000) {
      setInterval(reloadActivity, 60000);
   }

   // Formulaires de réévaluation
   $(document).on('submit', '.formReevaluate', function(e) {
      $.blockUI({
         message: '<h1>Réévaluation de la soumission</h1>'
      });
      var meForm = $(this);
      setTimeout(function() {
         $.ajax({
            type: 'POST',
            url: meForm.attr('action') + '&bEvaluate=1&sOnlyBlock=mainContent',
            data: meForm.serialize(),
            async: false
         });
         waitForEvalResults(meForm.parent(), meForm.attr('action') + '&sOnlyBlock=mainContent');
      }, 350);
      return false;
   });
}


function previewMsg(button, forEdit) {
   var form = $(button).closest('form');
   form.find('.messagePreview').html("…");
   $.post($('.navigbox a:last').attr('href') + '&sView=preview' + (forEdit ? 'Edit' : ''), form.serialize(), function(result) {
      form.find('.messagePreview').empty().append($(result).find('.thread-message' + (forEdit ? '-contents' : '')));
      SyntaxHighlighter.highlight();
   });
}
