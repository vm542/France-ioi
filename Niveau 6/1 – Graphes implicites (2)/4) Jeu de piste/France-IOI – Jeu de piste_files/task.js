function initCodeTabs()
{
   $("div.codeTabs").each(function()
   {
      var me = $(this);

      // Build the menu
      var ul = $("<ul>");
      $(this).children("div").each(function (index)
      {
         $(this).attr('id', 'tabs-'+index);
         var title = $(this).attr('title');
         var lang = $(this).attr('lang');
         if (typeof title === 'undefined' || title === false || title === '')
            title = lang;
         $(ul).append('<li><a href="#tabs-'+index+'">'+lang+'</li>');
      });
      me.prepend(ul);

      // Creates the tabs
      me.tabs();

      // Select the last one for the selected langage
      // Should be only one but who knows in the future...
      var allDivs = $(this).children("div").get().reverse();
      $(allDivs).each(function (index)
      {
         sLang = sSelectedLanguage;
         if(sLang == 'Cpp')
            sLang = "C++";
         if ($(this).attr('lang') == sLang)
            me.tabs('select', allDivs.length - 1 - index);
      });
   });
}


$(function() {
   if (typeof idTask != 'undefined')
   {
      $.ajax({
         type: "GET",
         url: "../epistemes/ajaxLog.php?idTask="+idTask+"&sAction=taskSeen",
         datatype: "String",
         success: function(msg){

         }
      });
   }

    /* Warning for IE9 : the editor is not working corectly */
    //$.migrateMute = false;
    var ua = $.browser;//deprecated
    if (ua.msie && ua.version.slice(0, 1) == "9")
       $("#warningIE").show();
    else
       $("#warningIE").hide();

   /* Global tabs */
   // Name of the global tab to select
   if (typeof(sTab)=='undefined')
      sTab = 'task';

   var sLogTabCLicks = false;
   var editorLoaded = $('#allEditors').length == 0;
   $("#task-tabs").tabs(
   {
      select: function(event, ui)
      {
         if (sLogTabCLicks)
         {
            var name = ui.panel.id.charAt(0).toUpperCase() + ui.panel.id.substr(1);
            var action = "Tab"+name;
            $.ajax({
               type: "GET",
               url: "../epistemes/ajaxLog.php?idTask="+idTask+"&sAction="+action,
               datatype: "String",
               success: function(msg){
               }
            });
         }

         if (ui.panel.id == "correction") {
            if (!bCorrectionRead) {
               jQuery.get("task.php?idChapter="+idChapter+"&idTask="+idTask+"&sTab=correction&sOnlyBlock=mainContent");
               bCorrectionRead = true;
            }
         }
         else if (ui.panel.id == "editor"){
            if (!editorLoaded) {
               setTimeout(function() {
                  $("#task-tabs").tabs("option", "disabled", [ 0, 2, 3, 4 ]);
                  startEditor(function() {
                     editorLoaded = true;
                     $("#task-tabs").tabs("option", "disabled", []);
                  });
               }, 20);
            } else {
               getFocusEditor();
            }
         }
         else if (ui.panel.id == "epistemes") {
            var elem = document.getElementById("graph_frame");
            if (elem != null)
               elem.contentDocument.location.reload(true);
         }
      }
   });

   /* Statement tab */
   $("[name=goEditor]").click(function()
   {
      $("#task-tabs").tabs("select", "editor");
      $("body, html").scrollTop($("#task-tabs").offset().top);
   });

   initCodeTabs();
   $("#task-tabs").tabs("select", sTab);

   if($("#buttonSave").length > 0)
   {
      /* Editor tab */
      // Tooltips
      MyTooltip($("#buttonSave"), $("#tooltip-buttonSave").html());
      MyTooltip($("#buttonTest"), $("#tooltip-buttonTest").html());
      MyTooltip($("#buttonTestAll"), $("#tooltip-buttonTestAll").html());
      MyTooltip($("#buttonSubmit"), $("#tooltip-buttonSubmit").html());
      MyTooltip($("#buttonTestOne"), $("#tooltip-buttonTestOne").html());
      MyTooltip($("#buttonAddTest"), $("#tooltip-buttonAddTest").html());
      MyTooltip($(".buttonReevaluate"), $("#tooltip-buttonReevaluate").html());

      // Interface modification
      $("#linkUpload, #linkEditorOnline").click(function()
      {
         $("#allEditors, #submitArea, #uploadForm").toggle();
         return false;
      });
      $("#submitArea").hide();

      $(document).on('click', ".evaluation-correction a", function()
      {
         $("#task-tabs").tabs("select", "correction");
         $("body, html").scrollTop($("#task-tabs").offset().top);
         return false;
      });

      $(document).on('submit', '.formReevaluate', function() {
         $(this).find('.buttonReevaluate').qtip("hide");
         $("#task-tabs").tabs("select", "editor");
         var meForm = $(this);
         var count = 0;
         var startReeval = function() {
            if (editorLoaded) {
               $("#task-tabs").tabs("select", "activity");
               meForm.submit();
            } else if (count < 50) {
               count++;
               setTimeout(startReeval, 400);
            }
         };
         startReeval();
         return false;
      });
   }
});


function previewMsg(button) {
   var form = $(button).closest('form');
   form.find('.messagePreview').html("…");
   $.post($(button).attr('data-url'), form.serialize(), function(result) {
      form.find('.messagePreview').empty().append($(result).find('.thread-message'));
      SyntaxHighlighter.highlight();
   });
}
