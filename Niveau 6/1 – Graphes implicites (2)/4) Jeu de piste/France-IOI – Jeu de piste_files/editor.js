function setCookie(key, value) {
   var expires = new Date();
   expires.setTime(expires.getTime() + 31536000000); //1 year
   document.cookie = key + '=' + value + ';expires=' + expires.toUTCString();
}
function getCookie(key) {
   var keyValue = document.cookie.match('(^|;) ?' + key + '=([^;]*)(;|$)');
   return keyValue ? keyValue[2] : null;
}

/// @brief Logging function working even if the console does not exist
function consoleLog(s){
    if (true) {
    } else if (typeof console!="undefined" && typeof console.debug!="undefined") {
        console.log(s);
    } else {
        //alert(s);
    }
}

/// @brief Log informations when an AJAX error occured
function alertAJAXError(XMLHttpRequest, textStatus, errorThrown)
{
    var error    = 'Informations : <ul>';
    error       += '<li>'+textStatus+'</li>';
    error       += '<li>'+errorThrown+'</li>';
    error       += '</ul>';
    //consoleLog(XMLHttpRequest);
    //consoleLog(error);
}

/// @brief Our main class
function EditorAJAX()
{
   /// @brief Constants
   this.maxNbSources = 20;
   this.maxNbTests = 30;
   this.autoSavePeriod = 60*1000; // in milliseconds
   
   this.quit = false;
   
   var me = this; /// @brief For callback
   
   /// @brief Translate a word
   this.translate = function(word)
   {
      return editAreaLoader.translate(word, editorLang, "word");
   }
   
   /// @brief Initalize
   this.initialize = function(callback)
   {
      this.callback = callback;
      // Cela ne marche que pour firefox et IE, mais c'est deja ca...
      $(window).bind('beforeunload', function() {
            if (me.isModifiedFile())
            {
               //me.quit = true;
               //me.save_callback();
               // Demande confirmation avant de quitter
               return me.translate("unsavedChanges");
            }
      });

      // Get user data from the server
      this.getUserData();
      // Init everything
      this.initTextareas();
      this.initButtons();
      this.planAutoSave();
      this.activitySimu();
   }
   
   /// @brief Init the text areas
   this.initTextareas = function()
   {
      // Init the two textarea
      var sourcesEditArea = me.getPrototype(false);
      sourcesEditArea.id = "sourcesTextArea";
      sourcesEditArea.syntax = "cpp";
      editAreaLoader.init(sourcesEditArea);

      var testsEditArea = me.getPrototype(true);
      testsEditArea.id = "testsTextArea";
      testsEditArea.syntax = "test";
      editAreaLoader.init(testsEditArea);

   }   
   
   this.getPrototype = function(bIsTest)
   {
      basic = {
         font_size: "10",
         toolbar: "franceioi_newtab, |, "
            + "search, go_to_line, fullscreen, |, undo, redo, |, select_font,|, "
            + "reset_highlight, word_wrap, |, help",
         is_multi_files: true,
         allow_resize: "both",
         show_line_colors: true,
         min_width: 0,
         min_height: 0,
         replace_tab_by_spaces: replace_tab_by_spaces,
         allow_toggle: false,
         language: editorLang,
         browsers: "all",
         word_wrap: true, // Si onutilise pas ça comme valeur par défaut, il semble qu'il y ait un bug avec chrome...
         plugins: "franceioi",
         franceioi_newtab_callback: "EditorAJAX.newtab_callback",
         EA_file_close_callback: "EditorAJAX.closefile_callback",
         save_callback: "EditorAJAX.save_callback",
         EA_load_callback: "EditorAJAX.load_callback",
         EA_file_switch_on_callback:"EditorAJAX.file_switch_on_callback",
         start_highlight: true
      };

      if(!bIsTest)
      {
         basic.syntax_selection_allow = "ada,c,cpp,eiffel,java,javascool,objC,ocaml,pas,python";
      }
   
      return basic;
   }


   this.applyMode = function(bIsBasic)
   {
      if (bIsBasic !== undefined)
         this.UserData.bIsBasic = bIsBasic;
      if (this.UserData.bIsBasic)
         this.goBasicMode();
      else
         this.goExpertMode();
      editAreaLoader.execCommand('sourcesTextArea', 'update_size()');
      editAreaLoader.execCommand('testsTextArea', 'update_size()');
   }
   this.goBasicMode = function()
   {
      this.UserData.bIsBasic = true;
      $(".editor-options").addClass('basic');
      $("#frame_sourcesTextArea").contents().find("#tab_browsing_area, #toolbar_1, #toolbar_2").hide();
      $("#frame_testsTextArea").contents().find("#toolbar_1, #toolbar_2").hide();
      $("#buttonAddTestDiv").show();
   }
   this.goExpertMode = function()
   {
      this.UserData.bIsBasic = false;
      $(".editor-options").removeClass('basic');
      $("#frame_sourcesTextArea").contents().find("#tab_browsing_area, #toolbar_1, #toolbar_2").show();
      $("#frame_testsTextArea").contents().find("#toolbar_1, #toolbar_2").show();
      $("#buttonAddTestDiv").hide();
   }


   this.updateActivity = function()
   {
      $('.tabsUpdateMessage').show();
      // We need to update the activity page
      $.ajax({
         type:'GET',
         url: "task.php?idChapter="+idChapter+"&idTask="+idTask+"&sOnlyBlock=mainContent",
         success: function(result, textStatus, XMLHttpRequest)
         {
            var dom = $(result);

            var content = dom.find("#task-tabs #help");
            $("#task-tabs #help").html(content.html());
            var content = dom.find("#task-tabs #activity");
            $('#task-tabs #activity .toggleHeader').each(function() {
               if (this.checked) {
                  content.find('#' + $(this).attr('id')).attr('checked', true);
               }
            });
            $("#task-tabs #activity").html(content.html());
            var content = dom.find("#task-tabs #correction");
            $("#task-tabs #correction").html(content.html());

            MyTooltip($(".buttonReevaluate"), $("#tooltip-buttonReevaluate").html());
            initCodeTabs($("#task-tabs #correction"));
            SyntaxHighlighter.highlight();
            if (typeof MathJax !== "undefined") {
               MathJax.Hub.Queue(["Typeset",MathJax.Hub]);
            }
            me.activitySimu();
         },
         error: function (XMLHttpRequest, textStatus, errorThrown)
         {
            alertAJAXError(XMLHttpRequest, textStatus, errorThrown)
         },
         complete: function() {
            $('.tabsUpdateMessage').hide();
         }
      });
   }

   this.simuNumActivity = 1;
   this.activitySimu = function()
   {
      if (typeof simulationInstance === "undefined") return;

      $('.activityList .evaluation-results-table').each(function() {
         var nbBad = $(this).find('.evaluation-result-error, .evaluation-result-failure, .evaluation-result-perffail').length;
         var fe = $(this).find('.evaluation-result-' + (nbBad == 0 ? 'success' : 'failure') + ' pre').eq(0);

         if (fe.length > 0) {
            var json = fe.html();
            var td = fe.parent();

            try {
               $.parseJSON(json);
               var idSimu = 'simuTestActivity' + me.simuNumActivity;
               td.html($('<div>').attr('id', idSimu));
               instance = createInstance(idSimu, json, {
                  reset: false,
                  play: false,
                  replay: true,
               });
               instance.startSimulation();
            }
            catch(e) {}
            me.simuNumActivity++;
         }
         $(this).find('.evaluation-result-failure pre, .evaluation-result-success pre').remove();
      });
   }

   this.waitForEvalResults = function(divRes, idSubmission) {
      var resultUrl = $('#evaluationLink').attr('href') + '&sOnlyBlock=mainContent';
      if (idSubmission != undefined) {
         resultUrl += '&idSubmission=' + idSubmission;
      }
      var retryDelay = 1000;
      var lookForEval = function() {
         var finished = false;
         $.ajax({
            type: 'GET',
            url: resultUrl,
            async: false,
            success: function(result, textStatus, XMLHttpRequest)
            {
               var dom = $(result);
               var content = dom.find('#eval_results').html();

               if (content.length != 0) {
                  if (divRes) {
                     if (dom.find("#debugInfos").size() != 0) {
                        content += dom.find("#debugInfos").html();
                     }

                     divRes.html(content);
                     if (parseInt($('.evaluation-result-total td:last-child').text()) == 100) {
                        $('#noSaveCheck').show();
                     }

                     // There is a simulation !
                     if (typeof simulationInstance !== "undefined") {
                        // Find first error
                        var nbBad = divRes.find('.evaluation-result-error, .evaluation-result-failure, .evaluation-result-perffail').length;
                        var fe = divRes.find('.evaluation-result-' + (nbBad == 0 ? 'success' : 'failure') + ' pre').eq(0);

                        if (fe.length > 0) {
                           var jsonServer = fe.html();
                           var td = fe.parent();

                           try {
                              $.parseJSON(jsonServer);
                              // As general as possible...
                              td.html('<div id="simuTest"></div>');
                              instance = createInstance("simuTest", jsonServer, {
                                 reset: false,
                                 play: false,
                                 replay: true,
                              })
                              instance.startSimulation();
                           }
                           catch(e) {}
                        }
                        divRes.find('.evaluation-result-failure, .evaluation-result-success').find('pre').remove();
                     }
                  }

                  finished = true;
               }
            },
            error: function (XMLHttpRequest, textStatus, errorThrown)
            {
               alertAJAXError(XMLHttpRequest, textStatus, errorThrown)
               alert(me.translate("XHRerror") + me.translate("invalidAnswer"));
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
            me.updateActivity();
            if (idSubmission == undefined) {
               me.planAutoSave();
               this.saveRunning = false;
            }
         }
      };
      lookForEval();
   };

   /// @brief Init the buttons
   this.initButtons = function()
   {
      $(document).off('submit', '.formReevaluate').on('submit', '.formReevaluate', function(e) {
         e.preventDefault();
         $.blockUI({
            message: '<h1>Réévaluation de la soumission</h1>'
         });
         var meForm = $(this);
         setTimeout(function() {
            $.ajax({
               type: 'POST',
               url: meForm.attr('action') + '&sOnlyBlock=mainContent',
               data: meForm.serialize(),
               async: false
            });
            me.waitForEvalResults(null, meForm.find('[name=idSubmission]').val());
         }, 350);
         return false;
      });

      $("#buttonSave").click(function() {
         me.save_callback();
      });

      $("#buttonSubmit").click(function() {
         $("#eval_results").html('');

         me.callAjax(
            me.translate('submit'),
            function(){
               var file = editAreaLoader.getCurrentFile("sourcesTextArea");
               if(file == undefined || file.id == "") {
                  alert(me.translate("noTestSelected"));
                  return;
               }
               var bNoSaveCheck = document.getElementById("bNoSaveCheck");
               $('#bNoSave').val(bNoSaveCheck != undefined && bNoSaveCheck.checked ? 1 : 0);
               $("#sSourceContents").attr('value', file.text);
               $("#sExtension").attr('value', me.getLanguageForServer(file.syntax));

               $.ajax({
                  type: 'POST',
                  url: $("#submitForm").attr('action') + '&sOnlyBlock=mainContent',
                  data: $("#submitForm").serialize(),
                  async: false
               });

               me.waitForEvalResults($('#eval_results'));
            },
            function(errorTxt){
               alert(me.translate("XHRerror")+errorTxt);
            },
            null,
            null,
            false
         );

         return false;
      });

      $("#buttonTestOne").click(function() {
         $("#tests_results").html('');

         var file = editAreaLoader.getCurrentFile("sourcesTextArea");
         if(file == undefined || file.id == "") {
            alert(me.translate("noSourceSelected"));
            return;
         }

         var divRes = $("#tests_results");
         me.callAjax(
            me.translate("testing"),
            function(result) {
               me.waitForEvalResults(divRes);

               var dom = divRes.clone();
               var output = dom.find('.evaluation-result-success, .evaluation-result-failure');
               if (output.length > 0) {
                  var outputChars = $('<pre class="formatted-source output">');
                  outputChars.text(output.find('pre').eq(0).text());
                  divRes.html('<p style="margin-top: 0;">Résultat :</p><div style="float: left;">↳</div>').append(outputChars);
                  if (dom.find('.evaluation-result-warning').length > 0) {
                     divRes.append(result);
                     divRes.find('.evaluation-result-warning ~ tr').remove();
                  }
               }
               else {
                  divRes.html(result);
                  var errorCells = divRes.find('td:not(:nth-child(3))');
                  if (errorCells.length == 3) {
                     errorCells.remove();
                  }
               }
            },
            function(errorTxt){
               alert(me.translate("XHRerror")+errorTxt);
               divRes.html(me.translate("evalError"));
            },
            "lycee",
            file.id
         );
      });

      $("#buttonAddTest").click(function() {
         me.newtab_callback("testsTextArea");
      });

      $("#buttonTest").click(function() {
         $("#tests_results").html('');

         var file = editAreaLoader.getCurrentFile("sourcesTextArea");
         if(file == undefined || file.id == "") {
            alert(me.translate("noSourceSelected"));
            return;
         }

         var testFile = editAreaLoader.getCurrentFile("testsTextArea");
         if(testFile == undefined || testFile.id == "") {
            alert(me.translate("noTestSelected"));
            return;
         }
         var testId = testFile.id.substr(testFile.id.charAt(0) == 'i' ? 2 : 3);

         var divRes = $("#tests_results");
         me.callAjax(
            me.translate("testing"),
            function(result) {
               me.waitForEvalResults(divRes);
            },
            function(errorTxt){
               alert(me.translate("XHRerror")+errorTxt);
               divRes.html(me.translate("evalError"));
            },
            testId,
            file.id
         );
      });

      $("#buttonTestAll").click(function() {
         $("#tests_results").html('');

         var file = editAreaLoader.getCurrentFile("sourcesTextArea");
         if(file == undefined || file.id == "") {
            alert(me.translate("noSourceSelected"));
            return;
         }

         var empty = true;
         for(var f in editAreaLoader.getAllFiles("testsTextArea")) {
            empty = false;
            break;
         }

         if(empty) {
            alert(me.translate("noTest"));
            return;
         }

         var divRes = $("#tests_results");
         me.callAjax(
            me.translate("testing"),
            function(result) {
               me.waitForEvalResults(divRes);
            },
            function(errorTxt){
               alert(me.translate("XHRerror")+errorTxt);
               divRes.html(me.translate("evalError"));
            },
            "all",
            file.id
         );
      });
   }






   /// @brief Creates a new tab if there is not already too many ones
   this.newtab_callback = function(editAreaId)
   {
      var isTests = (editAreaId == "testsTextArea");
      var filesList = editAreaLoader.getAllFiles(editAreaId);
      var newId;

      for(newId = 1; ; newId++)
         if(filesList[(isTests ? "in" : "Code") + newId] == undefined)
            break;

      if(isTests)   {
         if(newId > this.maxNbTests) {
            alert(this.translate("maxNbTests").replace("%d", this.maxNbTests));
            return;
         }
      } else {
         if(newId > this.maxNbSources) {
            alert(this.translate("maxNbSources").replace("%d", this.maxNbSources));
            return;
         }
      }

      
      var NewName = '';
      for(var prefix in isTests ? {'in':"", 'out':""} : {"Code":"Code"}) {
         if(NewName == '')
            NewName = prefix + newId.toString();
         editAreaLoader.openFile(editAreaId, {
            id: prefix + newId.toString(),
            title: prefix + newId.toString(),
            text: isTests ? this.translate("commentExample") : "",
            syntax: isTests ? undefined : this.getLanguageFromServer($("#selectLanguageSelection").val())
         });

         editAreaLoader.setFileEditedMode(editAreaId, prefix + newId.toString(), true);
      }
      return NewName;
   }

   /// @brief Was a callback already called
   this.closefile_callback_called = false;
   
   /// @brief Close a tab
   this.closefile_callback = function (infos) {
      if(this.closefile_callback_called)
         return true;
      this.closefile_callback_called = true;
      try {
         if(confirm(this.translate("sureDel"))) {
            var isTests = (infos.id.indexOf("in") == 0) || (infos.id.indexOf("out") == 0);

            // Build the list of tab we need to close / delete
            var ids = {};
            if(isTests)   {
               var i = infos.id.replace("in", "").replace("out", "");
               ids["in"+i] = "";
               ids["out"+i] = "";
               // TODO : add error messages
               if(i <= this.UserData.nbDefaultTests)
                  return false;
            } else
               ids[infos.id] = "";

            // Tells EditArea to close them
            for(var id in ids)
               editAreaLoader.closeFile(isTests ? "testsTextArea" : "sourcesTextArea", id);

            // Deletes them from the DB
            this.callAjax(
               me.translate('Delete'),
               function(){},
               function(errorTxt){
                  alert(me.translate("delError")+errorTxt); }
               );
         }
         return false;
      } finally {
         this.closefile_callback_called = false;
      }
   }

   /// @brief Save tab contents
   this.save_callback = function(editAreaId)
   {
      setCookie("area_font_size",
         $("#frame_sourcesTextArea").contents().find("#area_font_size").val());
      setCookie("a_word_wrap",
         !$("#frame_sourcesTextArea").contents().find("#a_word_wrap > img").hasClass('editAreaButtonNormal'));
   
      this.callAjax(
         me.translate('Save'),
         function(){},
         function(errorTxt){
         alert(me.translate("saveError")+errorTxt); }
      );
   }

   
   this.selectFirstForComboLanguage = function()
   {
      var sComboLanguage = $("#selectLanguageSelection").val();
      var filesList = editAreaLoader.getAllFiles("sourcesTextArea");
      for(var name in filesList)
      {
         var sLangProg = this.getLanguageForServer(filesList[name].syntax);
         if(sLangProg == sComboLanguage)
         {
            this.select("sourcesTextArea",name);
            this.applyMode();
            return;
         }
      }
      first = this.newtab_callback("sourcesTextArea");
      this.applyMode();
      this.changeLanguageCombo(sComboLanguage);
   }
   
   
   
   
   /// @brief Load tab contents
   this.numLoaded = 0;
   this.load_callback = function(editAreaId) {   
      this.numLoaded = this.numLoaded + 1;
//      return;
      // Load sources
      if(editAreaId == "sourcesTextArea") {
         var sComboLanguage = $("#selectLanguageSelection").val();      
         for(var id = 0; id < this.UserData.aSources.length; id++)
         {
            var Source = this.UserData.aSources[id];
            editAreaLoader.openFile(editAreaId, {
               id: Source.sName,
               title: Source.sName,
               text: Source.sSource,
               syntax: this.getLanguageFromServer(Source.sLang)
            });
         }
         $("#selectLanguageSelection").val(sComboLanguage);
         this.selectFirstForComboLanguage();
      }
      // Load test files
      else {
         var testsEmpty = true;
         for(var id = 0; id < this.UserData.aTests.length; id++)
         {
            var Test = this.UserData.aTests[id];
            //consoleLog(Test);
            for(var prefix in {"in":"", "out":""})
               editAreaLoader.openFile(editAreaId, {
                  id: prefix + (id+1).toString(),
                  title: prefix + (id+1).toString(),
                  text: Test[(prefix=='in')?'sInput':'sOutput']
               });
            testsEmpty = false;
         }
         //if(this.UserData.aTests.length == this.UserData.nbDefaultTests)
            //this.newtab_callback("testsTextArea");
         first = "in0";   
         this.select(editAreaId,first);
      }
      
      
      if(this.numLoaded == 2)
      {
         this.applyMode();
         $("#Editor").attr('style','opacity:1.0;');
         // Change close file for examples
      
         /*
         // Old : message saying delete is not possible
         $("#frame_testsTextArea").contents().find("#tab_browsing_list").find("img").slice(0,2*me.UserData.nbDefaultTests)
         .removeAttr("onclick")
         .click(function(){
               alert(me.translate("cantdelete"));
         });
         */
         // Remove the cross for the official tests
         $("#frame_testsTextArea").contents().find("#tab_browsing_list").find("img").
         slice(0,2*me.UserData.nbDefaultTests).
         remove();
      
         /*
         // Desactiv word-wrap : not working with chrome...
         var filesList = editAreaLoader.getAllFiles("sourcesTextArea");
         var firstSource = null;
         for(var file in filesList)
         {
            var id = filesList[file].id;
            if(firstSource == null)
               firstSource = id;
            this.select("sourcesTextArea",id);
            top["frame_sourcesTextArea"].eA.execCommand('toggle_word_wrap');
         }

         this.select("sourcesTextArea", firstSource);
         */


          //var area = $("#frame_sourcesTextArea").contents().find("textarea");
          //area.attr('style',area.attr('style')+';'+'white-space: nowrap');    
          //area.removeAttr('wrap');

          if(bLycees)
          {
             this.goBasicMode();
             $("#buttonSave").hide();
          }
          if(!bUserTests)
             $("#testsArea").hide();



          $("#frame_sourcesTextArea").width('100%');
          $("#frame_testsTextArea").width('100%');      

      
          this.select(editAreaId,first);
      
          this.callback();
      }
   }
   
   
   this.file_switch_on_callback = function(file)
   {
      if(file.syntax != 'test' && file.syntax != undefined)
         this.changeLanguageCombo(this.getLanguageForServer(file.syntax));
   }
   
   
   this.select = function(editAreaId,fileId)
   {
      $("#"+editAreaId).attr('disabled',false);
      frame =  top["frame_"+editAreaId];
      frame.eA.execCommand('switch_to_file',frame.eA.filesIdAssoc['tab_file_'+fileId]);
   }

   this.bDataLoaded = false;
   this.UserData = null;
   this.getUserData = function()
   {
      if(this.bDataLoaded)
         return;
      // TODO : show waiting sign
      $.ajax({
         type:'POST',
         url: 'editorAjax.php?sAction=get&idTask='+idTask+'&idChapter='+idChapter,
         dataType: "json",
         async: false,
         success: function(result, textStatus, XMLHttpRequest)
         {
            //consoleLog(result);
            if(!result)
               return;
            if(!result.bSuccess)
               return;
            me.UserData = result.aData
            /*
            if(!result)
               return callBackFailed(me.translate("invalidAnswer"));
            if(!result.bSuccess)
               callBackFailed(result.sError);
            */
         },
         error: function (XMLHttpRequest, textStatus, errorThrown)
         {
            alertAJAXError(XMLHttpRequest, textStatus, errorThrown)
            //callBackFailed(me.translate("invalidAnswer"));
         }
      });

      $(this.UserData.bIsBasic ? "#bButtonBasic" : "#bButtonExpert").hide();

      this.bDataLoaded = true;
   }
   
   
   /// @brief Is there a modified file ?
   this.isModifiedFile = function () {
      var filesList = editAreaLoader.getAllFiles("sourcesTextArea");
      for(var file in filesList)
         if(filesList[file].text != "" && filesList[file].edited)
            return true;
      var filesList = editAreaLoader.getAllFiles("testsTextArea");
      for(var file in filesList)
         if(filesList[file].text != "" && filesList[file].edited)
            return true;
      return false;
   }
   /*
   this.tags = {sourcesTextArea:{}, testsTextArea:{}};
   this.saveFlags = function()
   {
      var allFiles = editAreaLoader.getAllFiles("sourcesTextArea");
      $.each(allFiles, function(key, value) {
            me.tags.sourcesTextArea[key] = value.edited;
      });
      var allFiles = editAreaLoader.getAllFiles("testsTextArea");
      $.each(allFiles, function(key, value) {
            me.tags.testsTextArea[key] = value.edited;
      });
   }
   */
   this.setToNotModified = function()
   {
      var allFiles = editAreaLoader.getAllFiles("sourcesTextArea");
      $.each(allFiles, function(key, value) {
            editAreaLoader.setFileEditedMode("sourcesTextArea", key, false);
      });
      var allFiles = editAreaLoader.getAllFiles("testsTextArea");
      $.each(allFiles, function(key, value) {
            editAreaLoader.setFileEditedMode("testsTextArea", key, false);
      });
   }
   this.setToModified = function()
   {
      var allFiles = editAreaLoader.getAllFiles("sourcesTextArea");
      $.each(allFiles, function(key, value) {
            editAreaLoader.setFileEditedMode("sourcesTextArea", key, true);
      });
      var allFiles = editAreaLoader.getAllFiles("testsTextArea");
      $.each(allFiles, function(key, value) {
            editAreaLoader.setFileEditedMode("testsTextArea", key, true);
      });
   }   
   /*
   this.restoreFlags = function()
   {
      var allFiles = editAreaLoader.getAllFiles("sourcesTextArea");
      $.each(allFiles, function(key, value) {
         if (me.tags.sourcesTextArea[key] && !value.edited)
            editAreaLoader.setFileEditedMode("sourcesTextArea", key, true);
      });
      var allFiles = editAreaLoader.getAllFiles("testsTextArea");
      $.each(allFiles, function(key, value) {
         if (me.tags.testsTextArea[key] == true && value.edited == false)
            editAreaLoader.setFileEditedMode("testsTextArea", key, true);
      });
   }
   */
   /// @brief Autosaving
   this.currentTimeoutId = -1;
   this.planAutoSave = function() {
      if(this.currentTimeoutId != -1)
         clearTimeout(this.currentTimeoutId);
      this.currentTimeoutId = setTimeout(function(){me.autoSave();}, me.autoSavePeriod);
   }
   
   this.autoSave = function() {
      this.currentTimeoutId = -1;

      if(this.isModifiedFile())
      {
         //this.saveFlags();
         //this.setToNotModified();

         //editAreaLoader.execCommand('testsTextArea', 'set_editable', false);
         //editAreaLoader.execCommand('sourcesTextArea', 'set_editable', false);
         this.callAjax(
            '',
            function(){
               //editAreaLoader.execCommand('testsTextArea', 'set_editable', true);
               //editAreaLoader.execCommand('sourcesTextArea', 'set_editable', true);
            },
            function(){
               //me.restoreFlags();
            }
         );
      }
      else
         this.planAutoSave();
   }
   

   this.getLanguageForServer = function(sLangProg)
   {
      var ext2Lang = {'c':'C','cpp':'C++','ocaml':'OCaml','pas':'Pascal','java':'Java','javascool':'JavaScool','python':'Python','':'','':''};
      return ext2Lang[sLangProg];
   }
   this.getLanguageFromServer = function(sLangProg)
   {
      var ext2Lang = {'C':'c','C++':'cpp','OCaml':'ocaml','Pascal':'pas','Java':'java','JavaScool':'javascool','Python':'python','':'','':''};
      return ext2Lang[sLangProg];
   }   
   

   


   /// @brief Will make the AJAX call
   this.callAjax = function(message, callBackOk, callBackFailed, testToEvaluate, sourceToEvaluate, bUnblock)
   {
      if (message)
         $.blockUI({
            message: '<h1>'+message+'</h1>'
         });
      setTimeout(function(){
            me.saveAjax(message, callBackOk, callBackFailed, testToEvaluate, sourceToEvaluate, bUnblock);
        }, 350);
   }
   
   /// @brief Make the AJAX call   
   this.saveRunning = false;
   this.saveAjax = function(message, callBackOk, callBackFailed, testToEvaluate, sourceToEvaluate, bUnblock)
   {
      // Auto save detected, let's try later
      if (this.saveRunning)
      {
         //consoleLog("wait");
         clearTimeout(this.timeOutCall);
         this.timeOutCall = setTimeout(function(){
            me.saveAjax(message, callBackOk, callBackFailed, testToEvaluate, sourceToEvaluate, bUnblock);
         }, 1000);
      }
      clearTimeout(this.timeOutCall);

      this.saveRunning = true;
   
//      me.planAutoSave();   
   //   return callBackFailed("pojjp");
      // Acumulate data
      var params = {};

      var filesList = editAreaLoader.getAllFiles("sourcesTextArea");
      //consoleLog('Get all files');
      //consoleLog(filesList);
      params['sources'] = {};
      $.each(filesList, function(key, value) {
         params['sources'][key] = {
            'sSource' : value.text,
            'sLangProg' : me.getLanguageForServer(value.syntax)
         };
      });

      var filesList = editAreaLoader.getAllFiles("testsTextArea");
      params['tests'] = {};
      var num = 0;
      for(var id = 1; id < this.maxNbTests; id++)
         if(filesList["in"+id] != undefined) {
            num = num +1;
            params['tests'][id] = {};
            params['tests'][id]['sName'] = "test"+id;
            params['tests'][id]['sInput'] = filesList["in"+id].text;
            params['tests'][id]['sOutput'] = filesList["out"+id].text;
            params['tests'][id]['bSave'] = (id > this.UserData.nbDefaultTests)
         }

      if(testToEvaluate == 'lycee')
      {
         var id = this.maxNbTests;
         params['tests'][id] = {};
         params['tests'][id]['sName'] = "test";
         params['tests'][id]['sInput'] = $("[name=UniqueTest]").val();
         params['tests'][id]['sOutput'] = '';
         params['tests'][id]['bSave'] = false         
         testToEvaluate = num + 1;
      }
      
      if(testToEvaluate != undefined) {
         params['sTestToEvaluate'] = testToEvaluate;
         params['sSourceToEvaluate'] = sourceToEvaluate;
      }
      params['bBasicEditorMode'] = this.UserData.bIsBasic ? 1 : 0;

      params['idUser'] = idUser;

      //consoleLog(params);

      var jsonStr = YAHOO.lang.JSON.stringify(params);
      var data = {json: jsonStr};

      me.setToNotModified();

      $.ajax({
         type:'POST',
         url: "editorAjax.php?sAction=save&idChapter="+idChapter+"&idTask="+idTask,
         data: data,
         dataType: "json",
         async: (message == ''),
         success: function(result, textStatus, XMLHttpRequest)
         {
            if(!result)
               return callBackFailed(me.translate("invalidAnswer"));
            if(result.success)
            {
               // Mark all files as not modified
               //me.setToNotModified();
               callBackOk(result.html);
            }
            else
              callBackFailed(result.error);
         },
         error: function (XMLHttpRequest, textStatus, errorThrown)
         {
            me.setToModified();
            alertAJAXError(XMLHttpRequest, textStatus, errorThrown)
            callBackFailed(me.translate("invalidAnswer"));
         },
         complete: function()
         {
            if (bUnblock == undefined || bUnblock == true)
               $.unblockUI();
            me.planAutoSave();
            this.saveRunning = false;
         }
      });
   }



   this.comboToFile = function()
   {
      var sLangProg = $("#selectLanguageSelection").val();
      editAreaLoader.execCommand("sourcesTextArea","change_syntax",this.getLanguageFromServer(sLangProg));
   }
   this.changeLanguageCombo = function(sLangProg)
   {
      $("#selectLanguageSelection").val(sLangProg);
   }   
}
var EditorAJAX = new EditorAJAX();



function getFocusEditor()
{
   $("#frame_sourcesTextArea").contents().find("textarea").focus();
}

function startEditor(callback)
{
   $("#sourcesTextArea, #testsTextArea").attr('disabled', true);

   EditorAJAX.initialize(function()
   {
      $('.editorLoadingMessage').remove();
      $("#uploadForm").hide();
      $("#submitArea").show();
      EditorAJAX.applyMode();
      $("#selectTestsInterface").find("a:" + (bLycees ? "fir" : "la") + "st-child").click();

      // Change font-size
      if (getCookie("area_font_size") !== null)
      {
         $("#frame_sourcesTextArea").contents().find("#area_font_size").val( getCookie("area_font_size") );
         $("#frame_sourcesTextArea").contents().find("#area_font_size").change();
         var a_word_wrap = (getCookie("a_word_wrap") === "true");
         if (
            ($("#frame_sourcesTextArea").contents().find("#a_word_wrap > img").hasClass('editAreaButtonNormal') && a_word_wrap) ||
            ($("#frame_sourcesTextArea").contents().find("#a_word_wrap > img").hasClass('editAreaButtonSelected') && !a_word_wrap)
         )
         {
            $("#frame_sourcesTextArea").contents().find("#a_word_wrap").click();
         }
      }
      if (callback != null)
         callback();
   });

   $("#selectLanguageSelection").change(function(){EditorAJAX.comboToFile()}).change();
   $("#bButtonBasic").click(function(){EditorAJAX.applyMode(true)});
   $("#bButtonExpert").click(function(){EditorAJAX.applyMode(false)});

   return true;
}

