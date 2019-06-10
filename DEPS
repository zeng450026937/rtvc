vars = {
  # M74 release
  'webrtc_git': 'https://webrtc.googlesource.com',
  'webrtc_version': 'cc1b32545db7823b85f5a83a92ed5f85970492c9',

  'pjsip_svn': 'http://svn.pjsip.org/repos/pjproject',
  'resiprocate_git': 'https://github.com/resiprocate/resiprocate.git',

  'checkout_webrtc': True,
  'checkout_pjsip': False,
  'checkout_resiprocate': False,

  'apply_patches': True,
}

deps = {
  'src': {
    'url': Var("webrtc_git") + '/src.git' + '@' + Var("webrtc_version"),
    'condition': 'checkout_webrtc',
  },
  'src/yealink/third_party/pjsip': {
    'url': Var("pjsip_svn") + '/trunk',
    'condition': 'checkout_pjsip',
  },
  'src/yealink/third_party/resiprocate': {
    'url': Var("resiprocate_git"),
    'condition': 'checkout_resiprocate',
  },
}

hooks = [
  {
    'name': 'patch_webrtc',
    'condition': 'checkout_webrtc and apply_patches',
    'pattern': 'src/yealink',
    'action': [
      'python',
      'src/yealink/script/apply_all_patches.py',
      'src/yealink/patches/config.json',
    ],
  },
  # download prebuild library.
]

recursedeps = [
  'src',
]
