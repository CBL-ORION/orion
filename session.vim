let g:syntastic_c_include_dirs = [
			\ 'lib',
			\ 'external/c-tap-harness/c-tap-harness/tests',
			\ 'external/kiss-fft/kiss-fft',
			\ 'external/kiss-fft/kiss-fft/tools'
			\ ]
let g:syntastic_cpp_include_dirs = g:syntastic_c_include_dirs

function! ORION_GetCorresponding()
	let b:tmpname = expand( '%:p' )
	if (match(b:tmpname, '\/lib\/.*\.c$') != -1)
		let b:basepath = substitute(b:tmpname, '\/lib\/.\+', '', '' )
		let b:filepart = substitute(b:tmpname, '.\+\/lib\/', '', '')
		let b:testfile = ''
		if match( b:filepart, '^t\/') != -1
			let b:file = substitute(b:filepart, '^t\/', '', '')
			return b:basepath . '/lib/' . b:file
		else
			let b:file = b:filepart
			return b:basepath . '/lib/t/' . b:file
		endif
	endif
	return ''
endfunction

function! ORION_GotoCorresponding()
	let file = ORION_GetCorresponding()
	let module = expand( '%:p' )
	let directory = fnamemodify(expand(file), ":p:h")
	if !isdirectory( directory )
		call mkdir(directory, "p")
	end
	if !empty(file)
		execute "edit " . file
	else
		echoerr("Cannot find corresponding file for: ".module)
	endif
endfunction

augroup ORION_project
	au!
	exe "autocmd BufRead ". expand("<sfile>:p:h")."/* call ORION_project_settings()"
augroup END

function! ORION_project_settings()
setl path+=lib

compiler gcc
let &l:makeprg='export CFLAGS="$CFLAGS -fPIC -Wall"; make PROD=1 BUILD_DEBUG=1 BUILD_ENABLE_ASAN=0 -j4'

nmap <buffer> <F5> :make<Return>
nmap <buffer> ,gg :call ORION_GotoCorresponding()<Return>

endfunction
