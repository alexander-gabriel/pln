;
; persistence.scm
;
; Utilities related to atom persistence
;
; Copyright (C) 2009 Linas Vepstas <linasvepstas@gmail.com>
;
; --------------------------------------------------------------------
; store-referers -- Store to SQL all hypergraphs that contain given atom
;
; This stores all hypergraphs that the given atom participates in.
; It does this by recursively exploring the incoming set of the atom.

(define (store-referers atomo)
	(define (do-store atom)
		(let ((iset (cog-incoming-set atom)))
			(if (null? iset)
				(cog-ad-hoc "store-atom" atom)
				(for-each do-store iset)
			)
		)
	)
	(do-store atomo)
)

; --------------------------------------------------------------------
; load-referers -- Load from SQL all hypergraphs that contain given atom 
;
; This loads all hypergraphs that the given atom participates in.
; It does this by recursively exploring the incoming set of the atom.

(define (load-referers atom)
	(if (not (null? atom))
		; The cog-ad-hoc function for this is defined to perform
		; a recursive fetch.
		; We do an extra recursion here, in case we were passed a list.
		(if (pair? atom)
			(for-each load-referers atom)
			(cog-ad-hoc "fetch-incoming-set" atom)
		)
	)
)

; --------------------------------------------------------------------
