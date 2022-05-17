global vjxx_areas
global vjxx_weak_classifiers
global vjxx_strong_classifiers
global vjxx_cascade_classifier

section .rodata

vjxx_areas:
	incbin '../VJxx/model/area.vjxx.bin'

vjxx_weak_classifiers:
	incbin '../VJxx/model/weak_classifiers.vjxx.bin'

vjxx_strong_classifiers:
	incbin '../VJxx/model/strong_classifiers.vjxx.bin'

vjxx_cascade_classifier:
	incbin '../VJxx/model/cascade_classifier.vjxx.bin'
