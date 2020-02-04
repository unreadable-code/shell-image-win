{
    'target_defaults': {
        'defines': [
            '_WIN32_WINVER=0x0602',
            '_WIN32_WINNT=0x0602',
        ],
    },
    'targets': [
        {
            'target_name': 'addon',
            'include_dirs': [
                '<!(node -e "require(\'nan\')")',
            ],
            'sources': [
                'addon.cpp',
                'file_image.cpp',
            ],
            'link_settings': {
                'libraries': [
                    'Gdiplus.lib',
                ],
            },
        },
    ],
}
