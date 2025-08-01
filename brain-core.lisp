
(defclass conceptual-object ()
  ((name :accessor obj-name :initarg :name)
   (type :accessor obj-type :initarg :type)
   (properties :accessor obj-properties :initform (make-hash-table) :initarg :properties)))

(defun create-object (name type &rest properties)
  (let ((obj (make-instance 'conceptual-object :name name :type type)))
    (loop for (key val) on properties by 'cddr
          do (setf (gethash key (obj-properties obj)) val))
    (format t "~%New object created: ~a of type ~a~%" (obj-name obj) (obj-type obj))
    obj))

(defun query-prolog (query)
  (format t "~%Sending query to Prolog: ~a~%" query)
  (cond ((string= query "can_eat(cat, mouse).") "Yes")
        ((string= query "can_eat(dog, cat).") "No")
        (t "Unknown")))


(defun brain-main-loop ()
  (let ((my-cat (create-object 'whiskers 'animal :is-pet t :species 'cat)))
    (let ((my-mouse (create-object 'squeaky 'animal :is-pet nil :species 'mouse)))

      (format t "~%Lisp-based AGI decides to ask the reasoning module a question.")
      (let ((result (query-prolog "can_eat(cat, mouse).")))
        (if (string= result "Yes")
            (format t "~%Prolog says: The cat can eat the mouse. New knowledge acquired!~%")
            (format t "~%Prolog says: The cat cannot eat the mouse.~%")))

      (let ((result (query-prolog "can_eat(dog, cat).")))
        (if (string= result "Yes")
            (format t "~%Prolog says: The dog can eat the cat. New knowledge acquired!~%")
            (format t "~%Prolog says: The dog cannot eat the cat.~%"))))))