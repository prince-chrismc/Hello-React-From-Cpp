import { useState } from "react"
import { useFetch } from "react-async"
import { Button, Message } from 'semantic-ui-react'

import PopupModal from '../../containers/PopupModal'
import UserForm from '../forms/User'
import PendingMessage from '../messages/Pending'
// import { AddUser } from '../../core/services/List'

const ShowMessages = ({ isFulfilled, isPending, error }) => {
  return (
    <>
      { isPending && <PendingMessage message='Currently proccessing add of new user' />}
      { error && <Message error header='Oh no! Something went horribly wrong' content={error.message} />}
      { isFulfilled && <Message success header='Success! The operation completed without any issue' content='The user was successfully added' />}
    </>
  )
}

const CreateUser = ({ onAdd }) => {
  const [isSubmitting, setSubmmiting] = useState(false)
  const defaultUser = { id: 0, name: "John Doe", email: "john@example.com" }
  const { isFulfilled, isPending, error, run, cancel } = useFetch(process.env.API_URL + '/um/v1/users', {
    method: 'PUT',
    headers: {
      Accept: 'application/json',
      'Content-Type': 'application/json'
    },
  }, { onResolve: onAdd })

  const handleSubmit = (name, email) => {
    setSubmmiting(true)
    run({ body: JSON.stringify({ name, email }) })
  }

  const doClose = () => {
    cancel()
    setSubmmiting(false)
  }

  return (
    <PopupModal button={<Button content='Add' icon='user outline' labelPosition='left' color='green' />}
      header='Add New User' onClose={doClose}>

      {isSubmitting && <ShowMessages isFulfilled={isFulfilled} isPending={isPending} error={error} />}

      <UserForm user={defaultUser} handleSubmit={handleSubmit} disabled={isSubmitting} />
    </PopupModal>
  )
}

CreateUser.propTypes = {
  onAdd: PropTypes.func.isRequired
}

export default CreateUser
