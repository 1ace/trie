project('trie', 'c',
  version: '0.1',
  license: 'MIT',
  meson_version: '>= 0.46',
  default_options: ['c_std=c99']
)

cc = meson.get_compiler('c')

foreach a : [
  '-Werror=implicit-function-declaration',
  '-Werror=missing-prototypes',
  '-Werror=return-type',
  '-Werror=incompatible-pointer-types',
  '-Werror=undef',
]
  if cc.has_argument(a)
    add_project_arguments(a, language: 'c')
  endif
endforeach

python = import('python').find_installation()

test('sort order',
  python,
  args: files('order_check.py', 'egl_entrypoints.txt')
)

generated_source = custom_target('egl_trie',
  input: files('gen_lib.py', 'egl_entrypoints.txt'),
  output: 'egl_trie.h',
  command: [
    python, '@INPUT0@',
    '--entrypoints', '@INPUT1@',
    '--prefix', 'egl',
    '--header', '@OUTPUT@',
  ]
)

lib = library('foo',
  [files('lib.c'), generated_source]
)

test('trie',
  executable('trie_test', files('trie_test.c', 'packedstring.c', 'trie.c'))
)

test('use-test',
  executable('use-test',
    files('use-test.c'),
    link_with: lib
  )
)
