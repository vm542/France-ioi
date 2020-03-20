editAreaLoader.load_syntax["ocaml"] = {
	'DISPLAY_NAME' : 'OCaml',
	'COMMENT_SINGLE' : [],
	'COMMENT_MULTI' : {'(*' : '*)'},
	'QUOTEMARKS' : ['"'],
	'KEYWORD_CASE_SENSITIVE' : true,
	'KEYWORDS' : {
		'include' : ['include', 'open'],
		'constants' : ['true', 'false', 'assert', 'lazy'],
		'blocks' : [
			'do', 'done', 'downto', 'else', 'for', 'if',
			'match', 'rec', 'then', 'to', 'try', 'when', 'while',
			'with', 'begin', 'end', 'let', 'in', 'fun', 'function' ],
		'declarations' : [
			'class', 'exception', 'external', 'constraint', 'functor', 'inherit',
			'initializer', 'method', 'module', 'private', 'sig', 'struct', 'type',
			'val', 'mutable', 'virtual', 'of', 'object'
		],
		'operators' : [
			'and', 'asr', 'or', 'mod', 'lsl', 'lsr', 'lor', 'land', 'lxor', 'new', 'as'
		]
	},
	'OPERATORS' : [
		'@', '^', '+', '-', '*', '/', '%', '&', '$', '!', '?', '~',
		'.', ':', '<', '>', '|', ':=', '=', '+.', '-.', '*.', '/.' ],
	'DELIMITERS' : ['(', ')', '[', ']', '{', '}'],
	'REGEXPS' : {
		'typesvar' : {
			'search' : "()('[a-z][a-zA-Z0-9_]*)()",
			'class' : 'typesvar',
			'modifiers' : 'g',
			'execute' : 'after'
		}
	},
	'STYLES' : {
		'COMMENTS': 'color: #D00000;',
		'QUOTESMARKS': 'color: #6381F8;',
		'KEYWORDS' : {
			'include' : 'color: #009900;',
			'constants' : 'color: #EE0000;',
			'blocks' : 'color: #0000FF;',
			'declarations' : 'color: #48BDDF;',
			'operators' : 'color: #FF00FF;'
		},
		'OPERATORS' : 'color: #FF00FF;',
		'DELIMITERS' : 'color: #0038E1;',
		'REGEXPS' : {
			'typesvar' : 'color: #00EE00'
		}
	}
};
